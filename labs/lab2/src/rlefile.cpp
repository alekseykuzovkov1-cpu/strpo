#include "rlefile.hpp"
#include <iostream>
using namespace std;

// конструктор по умолчанию
RleFile::RleFile() : BaseFile(), remaining_count(0), last_char(0) {
    cout << "Конструктор RleFile (по умолчанию)" << endl;
}

// конструктор с параметрами
RleFile::RleFile(const char* path, const char* mode) : BaseFile(path, mode), remaining_count(0), last_char(0) {
    cout << "Конструктор RleFile (путь: " << path << ")" << endl;
}

// деструктор
RleFile::~RleFile() {
    if (write_count > 0) {
        unsigned char count_byte = (unsigned char)write_count;
        write_raw(&count_byte, 1);
        write_raw(&write_last_char, 1);
    }
    cout << "Деструктор RleFile" << endl;
}

size_t RleFile::write(const void* buf, size_t n_bytes) {
    if (!can_write() || n_bytes == 0) return 0;

    const unsigned char* data = (const unsigned char*)buf;
    
    for (size_t i = 0; i < n_bytes; ++i) {
        unsigned char current = data[i];

        // если это первый запуск или символ тот же, что был в конце прошлого буфера
        if (write_count > 0 && current != write_last_char) {
            // символ сменился -> сбрасываем старую накопленную пачку
            unsigned char count_byte = (unsigned char)write_count;
            write_raw(&count_byte, 1);
            write_raw(&write_last_char, 1);
            write_count = 0;
        }

        // накапливаем
        write_last_char = current;
        write_count++;

        // если счетчик переполнился, то принудительно сбрасываем
        if (write_count == 255) {
            unsigned char count_byte = 255;
            write_raw(&count_byte, 1);
            write_raw(&write_last_char, 1);
            write_count = 0;
        }
    }

    return n_bytes;
}

size_t RleFile::read(void* buf, size_t max_bytes) {
    unsigned char* dst = (unsigned char*)buf;
    size_t total_out = 0;

    // достаем остатки из прошлого вызова
    while (remaining_count > 0 && total_out < max_bytes) {
        dst[total_out++] = last_char;
        remaining_count--;
    }

    // если место в буфере еще есть, читаем новые пачки из файла
    while (total_out < max_bytes) {
        unsigned char pack[2]; // [счетчик, символ]
        if (read_raw(pack, 2) < 2) break; // конец файла

        int count = pack[0];
        unsigned char val = pack[1];

        // заполняем столько, сколько влезет
        while (count > 0 && total_out < max_bytes) {
            dst[total_out++] = val;
            count--;
        }

        // если пачка не влезла целиком, то запоминаем остаток
        if (count > 0) {
            remaining_count = count;
            last_char = val;
        }
    }
    return total_out;
}