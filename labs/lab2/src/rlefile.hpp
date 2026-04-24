#ifndef RLEFILE_HPP
#define RLEFILE_HPP

#include "basefile.hpp"

class RleFile : public BaseFile {
private:
    int remaining_count = 0;
    unsigned char last_char = 0;

    unsigned char write_last_char = 0;
    int write_count = 0;
public:
    // используем конструкторы базового класса
    RleFile();
    RleFile(const char* path, const char* mode);

    virtual ~RleFile();

    // переопределяем методы для сжатия/распаковки
    size_t write(const void* buf, size_t n_bytes);
    size_t read(void* buf, size_t max_bytes);
};

#endif