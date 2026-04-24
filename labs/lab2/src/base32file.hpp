#ifndef BASE32FILE_HPP
#define BASE32FILE_HPP

#include "basefile.hpp"

class Base32File : public BaseFile {
private:
    char custom_table[33];
    int decode_map[256];

    unsigned int write_bit_buffer = 0;
    int write_bit_count = 0;

    unsigned int bit_buffer = 0;
    int bit_count = 0;
    bool eof_reached = false;

    // вспомогательный метод для быстрой расшифровки символов
    void init_decode_map();

public:
    // конструкторы
    Base32File();
    Base32File(const char* path, const char* mode, const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    // деструктор
    virtual ~Base32File();
    
    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
};

#endif