#ifndef BASE32FILE_HPP
#define BASE32FILE_HPP

#include "basefile.hpp"

class Base32File : public BaseFile {
private:
    char custom_table[33];
    int decode_map[256];

    // Вспомогательный метод для быстрой расшифровки символов
    void init_decode_map();

public:
    // Конструкторы
    Base32File();
    Base32File(const char* path, const char* mode, const char* table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456");
    // Деструктор
    virtual ~Base32File();
    
    // Переопределяем виртуальные методы для кодирования/декодирования
    // Эти методы будут использоваться вместо прямых read_raw/write_raw
    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
};

#endif