#include "base32file.hpp"
#include <cstring>
#include <iostream>

using namespace std;

void Base32File::init_decode_map() {
    for (int i = 0; i < 256; ++i) decode_map[i] = -1;
    for (int i = 0; i < 32; ++i) {
        decode_map[(unsigned char)custom_table[i]] = i;
    }
}

// конструктор по умолчанию
Base32File::Base32File() : BaseFile() {
    strcpy(custom_table, "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    init_decode_map();
    cout << "Конструктор Base32File (по умолчанию)" << endl;
}

// главный конструктор (задание 2.2.1)
Base32File::Base32File(const char* path, const char* mode, const char* table) 
    : BaseFile(path, mode) 
{
    if (table && strlen(table) >= 32) {
        strncpy(custom_table, table, 32);
    } else {
        strcpy(custom_table, "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    }
    custom_table[32] = '\0';
    init_decode_map();
    cout << "Конструктор Base32File" << endl;
}

// деструктор
Base32File::~Base32File() {
    // если остались висячие биты
    if (can_write() && write_bit_count > 0) {
        char final_char = custom_table[(write_bit_buffer << (5 - write_bit_count)) & 0x1F];
        write_raw(&final_char, 1);
    }
    cout << "Деструктор Base32File" << endl;
}

// переопределенный метод записи (Base32 кодирование)
size_t Base32File::write(const void* buf, size_t n_bytes) {
    if (!can_write() || n_bytes == 0) return 0;

    // выделяем буфер с запасом
    size_t enc_capacity = (n_bytes * 8 + 8) / 5; 
    char* encoded = new char[enc_capacity];

    const unsigned char* raw = (const unsigned char*)buf;
    size_t dst_idx = 0;

    for (size_t i = 0; i < n_bytes; ++i) {
        write_bit_buffer = (write_bit_buffer << 8) | raw[i];
        write_bit_count += 8;
        
        // сбрасываем в файл всё, что делится на 5 бит
        while (write_bit_count >= 5) {
            encoded[dst_idx++] = custom_table[(write_bit_buffer >> (write_bit_count - 5)) & 0x1F];
            write_bit_count -= 5;
        }
    }
    
    // остатки лежат в write_bit_count и ждут следующего вызова write

    size_t actually_written = write_raw(encoded, dst_idx);
    delete[] encoded;
    
    return (actually_written == dst_idx) ? n_bytes : 0;
}

// переопределенный метод чтения (Base32 декодирование)
size_t Base32File::read(void* buf, size_t max_bytes) {
    if (!can_read() || max_bytes == 0) return 0;
    unsigned char* dst = (unsigned char*)buf;
    size_t dst_idx = 0;

    // цикл работает, пока мы не заполнили буфер пользователя
    while (dst_idx < max_bytes) {
        
        // если битов не хватает на байт, пробуем считать еще из файла
        while (bit_count < 8) {
            if (eof_reached) break;

            unsigned char byte_from_file;
            if (read_raw(&byte_from_file, 1) != 1) {
                eof_reached = true; // запоминаем, что файл закончился
                break;
            }

            int val = decode_map[byte_from_file];
            if (val == -1) continue; //пропускаем мусор

            bit_buffer = (bit_buffer << 5) | (val & 0x1F);
            bit_count += 5;
        }

        // если у нас есть достаточно бит (хотя бы 8), формируем байты
        while (bit_count >= 8 && dst_idx < max_bytes) {
            dst[dst_idx++] = (bit_buffer >> (bit_count - 8)) & 0xFF;
            bit_count -= 8;
        }

        // если битов всё еще мало (меньше 8) и файл пуст, то выходим
        if (bit_count < 8 && eof_reached) break;
    }

    return dst_idx;
}