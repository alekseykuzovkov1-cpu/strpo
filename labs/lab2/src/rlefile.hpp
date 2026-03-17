#ifndef RLEFILE_HPP
#define RLEFILE_HPP

#include "basefile.hpp"

class RleFile : public BaseFile {
public:
    // Используем конструкторы базового класса
    RleFile() : BaseFile() {}
    RleFile(const char* path, const char* mode) : BaseFile(path, mode) {}

    // Переопределяем методы для сжатия/распаковки
    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
};

#endif