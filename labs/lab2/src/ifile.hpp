#ifndef IFILE_HPP
#define IFILE_HPP

#include <cstddef>

class IFile {
public:
    // Чисто виртуальные функции (отмечены = 0)
    virtual bool can_read() const = 0;
    virtual bool can_write() const = 0;
    virtual size_t read(void* buf, size_t max_bytes) = 0;
    virtual size_t write(const void* buf, size_t n_bytes) = 0;

    // Обязательно виртуальный деструктор для интерфейса
    virtual ~IFile() {}
};

#endif