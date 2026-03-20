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

Base32File::Base32File() : BaseFile() {
    std::strcpy(custom_table, "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    init_decode_map();
    std::cout << "[CONSTRUCTOR] Base32File (default)" << std::endl;
}

Base32File::Base32File(const char* path, const char* mode, const char* table) 
    : BaseFile(path, mode) 
{
    cout << "[CONSTRUCTOR] Base32File" << endl;

    if (table && std::strlen(table) >= 32) {
        std::strncpy(custom_table, table, 32);
    } else {
        std::strcpy(custom_table, "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    }
    custom_table[32] = '\0';
    init_decode_map();
}

Base32File::~Base32File() {
    std::cout << "[DESTRUCTOR] Base32File" << std::endl;
}

size_t Base32File::write(const void* buf, size_t n_bytes) {
    if (!can_write() || n_bytes == 0) return 0;

    // Рассчитываем размер выходного буфера для Base32
    // (8 бит исходных данных преобразуются в 5-битные индексы)
    size_t enc_capacity = (n_bytes * 8 + 4) / 5;
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

    // Записываем "сырые" закодированные данные в файл через базовый класс
    size_t actually_written = write_raw(encoded, dst_idx);
    
    delete[] encoded;
    
    // Возвращаем количество обработанных исходных байт
    return (actually_written == dst_idx) ? n_bytes : 0;
}

size_t Base32File::read(void* buf, size_t max_bytes) {
    if (!can_read() || max_bytes == 0) return 0;

    // Сколько байт Base32 нужно прочитать, чтобы получить примерно max_bytes данных
    size_t enc_to_read = (max_bytes * 8) / 5;
    if (enc_to_read == 0) enc_to_read = 1;

    char* encoded = new char[enc_to_read];
    size_t actual_raw_read = read_raw(encoded, enc_to_read);

    unsigned char* dst = (unsigned char*)buf;
    unsigned int bit_buffer = 0;
    int bit_count = 0;
    size_t dst_idx = 0;

    for (size_t i = 0; i < actual_raw_read; ++i) {
        int val = decode_map[(unsigned char)encoded[i]];
        if (val == -1) continue; // Пропускаем неверные символы

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