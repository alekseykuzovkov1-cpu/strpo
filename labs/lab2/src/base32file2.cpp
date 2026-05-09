#include "base32file2.hpp"
#include <cstring>
#include <iostream>

using namespace std;

Base32File2::Base32File2(IFile* file) : target(file) {
    // копируем таблицу символов
    strcpy(custom_table, "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    // инициализируем карту для быстрого декодирования
    init_decode_map();
    cout << "Конструктор Base32File2 (композиция)" << endl;
}

Base32File2::~Base32File2() {
    cout << "Деструктор Base32File2 (удаление вложенного объекта...)" << endl;
    delete target; // освобождаем вложенный объект
}

void Base32File2::init_decode_map() {
    // заполняем карту значениями -1 (означает "символ не найден")
    memset(decode_map, -1, 256);
    for (int i = 0; i < 32; i++) {
        // каждому символу из custom_table сопоставляем его индекс (0-31)
        decode_map[(unsigned char)custom_table[i]] = (char)i;
    }
}

bool Base32File2::can_read() const { return target->can_read(); }
bool Base32File2::can_write() const { return target->can_write(); }

size_t Base32File2::write(const void* buf, size_t n_bytes) {
    const unsigned char* src = (const unsigned char*)buf;
    size_t written = 0;

    for (size_t i = 0; i < n_bytes; i++) {
        // разделяем байт на две части по 4 бита
        unsigned char high = (src[i] >> 4) & 0x0F;
        unsigned char low = src[i] & 0x0F;
        
        // пишем соответствующие символы из custom_table
        target->write(&custom_table[high], 1);
        target->write(&custom_table[low], 1);
        written++;
    }
    return written;
}

size_t Base32File2::read(void* buf, size_t max_bytes) {
    unsigned char* dest = (unsigned char*)buf;
    size_t read_total = 0;

    for (size_t i = 0; i < max_bytes; i++) {
        char chars[2];
        // пытаемся прочитать 2 символа из потока
        if (target->read(chars, 2) < 2) break; 

        // мгновенно получаем индексы через decode_map
        signed char high = decode_map[(unsigned char)chars[0]];
        signed char low = decode_map[(unsigned char)chars[1]];

        // если оба символа корректны (найдены в таблице)
        if (high != -1 && low != -1) {
            dest[i] = (unsigned char)((high << 4) | (low & 0x0F));
            read_total++;
        }
    }
    return read_total;
}