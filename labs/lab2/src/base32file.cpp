#include "base32file.hpp"
#include <cstring>
#include <iostream>
using namespace std;

int Base32File::decode_table_[256] = {0};

Base32File::Base32File() 
    : BaseFile(), bit_buffer_(0), bit_count_(0) {
    const char* default_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
    for (int i = 0; i < 32; ++i) {
        encode_table_[i] = default_table[i];
    }
    encode_table_[32] = '\0';
    init_decode_table();
}

Base32File::Base32File(const char* path, const char* mode) 
    : BaseFile(path, mode), bit_buffer_(0), bit_count_(0) {
    const char* default_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
    for (int i = 0; i < 32; ++i) {
        encode_table_[i] = default_table[i];
    }
    encode_table_[32] = '\0';
    init_decode_table();
}

Base32File::Base32File(const char* path, const char* mode, const char* encode_table)
    : BaseFile(path, mode), bit_buffer_(0), bit_count_(0) {
    if (encode_table) {
        for (int i = 0; i < 32 && encode_table[i]; ++i) {
            encode_table_[i] = encode_table[i];
        }
        encode_table_[32] = '\0';
    } else {
        const char* default_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
        for (int i = 0; i < 32; ++i) {
            encode_table_[i] = default_table[i];
        }
        encode_table_[32] = '\0';
    }
    init_decode_table();
}

Base32File::Base32File(FILE* file) 
    : BaseFile(file), bit_buffer_(0), bit_count_(0) {
    const char* default_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456";
    for (int i = 0; i < 32; ++i) {
        encode_table_[i] = default_table[i];
    }
    encode_table_[32] = '\0';
    init_decode_table();
}

Base32File::~Base32File() {
    // при разрушении записываем остаток, если он есть
    if (bit_count_ > 0 && can_write()) {
        // дописываем последний символ Base32
        int index = (bit_buffer_ << (5 - bit_count_)) & 0x1F;
        char last_char = encode_table_[index];
        BaseFile::write_raw(&last_char, 1);
    }
}

void Base32File::init_decode_table() {
    static bool initialized = false;
    if (!initialized) {
        for (int i = 0; i < 256; ++i) {
            decode_table_[i] = -1;  // -1 означает недопустимый символ
        }
        for (int i = 0; i < 32; ++i) {
            decode_table_[(unsigned char)encode_table_[i]] = i;
        }
        initialized = true;
    }
}

void Base32File::reset_state() {
    bit_buffer_ = 0;
    bit_count_ = 0;
}

size_t Base32File::write(const void* buf, size_t n_bytes) {
    if (!buf || n_bytes == 0 || !can_write()) {
        return 0;
    }
    
    const unsigned char* data = static_cast<const unsigned char*>(buf);
    size_t original_bytes_processed = 0;
    
    // временный буфер для закодированных данных
    // Base32 увеличивает размер примерно в 1.6 раза
    char encoded_buffer[256];
    int encoded_index = 0;
    
    for (size_t i = 0; i < n_bytes; ++i) {
        // добавляем байт в буфер
        bit_buffer_ = (bit_buffer_ << 8) | data[i];
        bit_count_ += 8;
        original_bytes_processed++;
        
        // извлекаем группы по 5 бит и кодируем
        while (bit_count_ >= 5) {
            int index = (bit_buffer_ >> (bit_count_ - 5)) & 0x1F;
            encoded_buffer[encoded_index++] = encode_table_[index];
            bit_count_ -= 5;
            
            // если буфер заполнен, записываем в файл
            if (encoded_index >= 250) {  // оставляем место для последней группы
                size_t written = BaseFile::write_raw(encoded_buffer, encoded_index);
                if (written != static_cast<size_t>(encoded_index)) {
                    return original_bytes_processed - 1;
                }
                encoded_index = 0;
            }
        }
    }
    
    // записываем оставшиеся закодированные данные
    if (encoded_index > 0) {
        size_t written = BaseFile::write_raw(encoded_buffer, encoded_index);
        if (written != static_cast<size_t>(encoded_index)) {
            return original_bytes_processed - 1;
        }
    }
    
    return original_bytes_processed;
}

size_t Base32File::read(void* buf, size_t max_bytes) {
    if (!buf || max_bytes == 0 || !can_read()) {
        return 0;
    }
    
    unsigned char* output = static_cast<unsigned char*>(buf);
    size_t bytes_decoded = 0;
    
    while (bytes_decoded < max_bytes) {
        // пока в битовом буфере недостаточно для формирования байта,
        // читаем новые закодированные символы
        while (bit_count_ < 8 && bytes_decoded < max_bytes) {
            // читаем один символ из файла
            char c;
            size_t read = BaseFile::read_raw(&c, 1);
            if (read != 1) {
                // достигнут конец файла - записываем остаток, если есть
                if (bit_count_ > 0) {
                    // неполный последний байт - игнорируем по спецификации Base32
                    bit_count_ = 0;
                }
                return bytes_decoded;
            }
            
            // декодируем символ
            int value = decode_table_[(unsigned char)c];
            if (value == -1) {
                // недопустимый символ в Base32
                return bytes_decoded;
            }
            
            // добавляем 5 бит в буфер
            bit_buffer_ = (bit_buffer_ << 5) | value;
            bit_count_ += 5;
        }
        
        // извлекаем байты из буфера
        while (bit_count_ >= 8 && bytes_decoded < max_bytes) {
            output[bytes_decoded++] = (bit_buffer_ >> (bit_count_ - 8)) & 0xFF;
            bit_count_ -= 8;
        }
    }
    
    return bytes_decoded;
}