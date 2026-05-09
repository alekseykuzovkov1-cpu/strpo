#ifndef BASEFILE_HPP
#define BASEFILE_HPP

#include <cstdio>
#include <cstddef>
#include "ifile.hpp"

class BaseFile : public IFile {
protected:
    FILE* file;
    bool readable;
    bool writable;

public:
    // конструкторы
    BaseFile();
    BaseFile(const char* path, const char* mode);
    BaseFile(FILE* existing_file, bool r = true, bool w = true);

    BaseFile(const BaseFile& other) = delete;
    BaseFile& operator=(const BaseFile& other) = delete;

    BaseFile(BaseFile&& other) noexcept;
    BaseFile& operator=(BaseFile&& other) noexcept;
    
    // деструктор 
    virtual ~BaseFile();

    // методы состояния
    bool is_open() const;
    bool can_read() const;
    bool can_write() const;

    // методы работы с данными
    size_t write_raw(const void* buf, size_t n_bytes);
    size_t read_raw(void* buf, size_t max_bytes);
    
    // обертки для последующего переопределения
    virtual size_t write(const void* buf, size_t n_bytes);
    virtual size_t read(void* buf, size_t max_bytes);

    // навигация
    long tell() const;
    bool seek(long offset);
};

#endif