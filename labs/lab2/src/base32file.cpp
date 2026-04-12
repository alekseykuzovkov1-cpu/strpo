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
    cout << "Деструктор Base32File" << endl;
}

// переопределенный метод записи (Base32 кодирование)
size_t Base32File::write(const void* buf, size_t n_bytes) {
    if (!can_write() || n_bytes == 0) return 0;

    // каждые 5 бит -> 1 символ Base32
    size_t enc_capacity = (n_bytes * 8 + 4) / 5 + 1;
    char* encoded = new char[enc_capacity];

    const unsigned char* raw = (const unsigned char*)buf;
    unsigned int bit_buffer = 0;
    int bit_count = 0;
    size_t dst_idx = 0;

    for (size_t i = 0; i < n_bytes; ++i) {
        bit_buffer = (bit_buffer << 8) | raw[i];
        bit_count += 8;
        while (bit_count >= 5) {
            encoded[dst_idx++] = custom_table[(bit_buffer >> (bit_count - 5)) & 0x1F];
            bit_count -= 5;
        }
    }
    
    if (bit_count > 0) {
        encoded[dst_idx++] = custom_table[(bit_buffer << (5 - bit_count)) & 0x1F];
    }

    // пишем закодированные данные в файл через базовый класс
    size_t actually_written = write_raw(encoded, dst_idx);
    
    delete[] encoded;
    
    // возвращаем количество обработанных исходных байт
    return (actually_written == dst_idx) ? n_bytes : 0;
}

// переопределенный метод чтения (Base32 декодирование)
size_t Base32File::read(void* buf, size_t max_bytes) {
    if (!can_read() || max_bytes == 0) return 0;

    // читаем из файла примерно столько, сколько нужно для распаковки в max_bytes
    size_t enc_to_read = (max_bytes * 8 + 4) / 5;
    char* encoded = new char[enc_to_read];
    size_t actual_raw_read = read_raw(encoded, enc_to_read);

    unsigned char* dst = (unsigned char*)buf;
    unsigned int bit_buffer = 0;
    int bit_count = 0;
    size_t dst_idx = 0;

    for (size_t i = 0; i < actual_raw_read; ++i) {
        int val = decode_map[(unsigned char)encoded[i]];
        if (val == -1) continue; 

        bit_buffer = (bit_buffer << 5) | (val & 0x1F);
        bit_count += 5;
        
        while (bit_count >= 8 && dst_idx < max_bytes) {
            dst[dst_idx++] = (bit_buffer >> (bit_count - 8)) & 0xFF;
            bit_count -= 8;
        }
    }

    delete[] encoded;
    return dst_idx;
}