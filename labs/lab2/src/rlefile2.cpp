#include "rlefile2.hpp"
#include <iostream>

using namespace std;

RleFile2::RleFile2(IFile* file) : target(file) {
    cout << "Конструктор RleFile2 (композиция)" << endl;
}

RleFile2::~RleFile2() {
    cout << "Деструктор RleFile2 (удаление вложенного объекта...)" << endl;
    delete target;
}

bool RleFile2::can_read() const { return target->can_read(); }
bool RleFile2::can_write() const { return target->can_write(); }

size_t RleFile2::write(const void* buf, size_t n_bytes) {
    if (n_bytes == 0) return 0;

    const unsigned char* src = (const unsigned char*)buf;
    size_t i = 0;
    size_t total_processed = 0;

    while (i < n_bytes) {
        unsigned char symbol = src[i];
        unsigned char count = 1;

        // считаем количество одинаковых байт (максимум 255 для одного байта счетчика)
        while (i + 1 < n_bytes && src[i + 1] == symbol && count < 255) {
            count++;
            i++;
        }

        // записываем пару [счетчик][символ] в следующий объект цепочки
        target->write(&count, 1);
        target->write(&symbol, 1);

        i++;
        total_processed += count;
    }

    return total_processed;
}

size_t RleFile2::read(void* buf, size_t max_bytes) {
    unsigned char* dest = (unsigned char*)buf;
    size_t total_decompressed = 0;

    while (total_decompressed < max_bytes) {
        unsigned char count;
        unsigned char symbol;

        // пробуем прочитать пару из target
        if (target->read(&count, 1) < 1) break;
        if (target->read(&symbol, 1) < 1) break;

        // распаковываем символ count раз
        for (int j = 0; j < count && total_decompressed < max_bytes; j++) {
            dest[total_decompressed++] = symbol;
        }
    }

    return total_decompressed;
}