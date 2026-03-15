#ifndef BASEFILE_HPP
#define BASEFILE_HPP

#include <cstdio>

class BaseFile {
private:
    FILE* file_;        // указатель на открытый файл
    char mode_[4];      // режим открытия файла
    
public:
    // конструкторы
    BaseFile();                                 // конструктор по умолчанию
    BaseFile(const char* path, const char* mode); // открытие файла по пути и режиму
    BaseFile(FILE* file);                        // использование готового указателя FILE*
    
    // деструктор
    virtual ~BaseFile();
    
    // методы для проверки состояния
    bool is_open() const;
    bool can_read() const;
    bool can_write() const;
    
    // методы для работы с файлом
    size_t write_raw(const void* buf, size_t n_bytes);
    size_t read_raw(void* buf, size_t max_bytes);
    long tell() const;
    bool seek(long offset);
    
    // методы-обертки
    virtual size_t write(const void* buf, size_t n_bytes);
    virtual size_t read(void* buf, size_t max_bytes);
};

#endif