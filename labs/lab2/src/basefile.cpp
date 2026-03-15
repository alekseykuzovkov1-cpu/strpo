#include "basefile.hpp"
#include <iostream>
using namespace std;

// конструктор по умолчанию
BaseFile::BaseFile() : file_(nullptr) {
    mode_[0] = '\0';
}

// конструктор с открытием файла
BaseFile::BaseFile(const char* path, const char* mode) : file_(nullptr) {
    if (path && mode) {
        file_ = fopen(path, mode);
        if (file_) {
            // сохраняем режим открытия для проверок can_read/can_write
            size_t i = 0;
            while (mode[i] && i < 3) {
                mode_[i] = mode[i];
                i++;
            }
            mode_[i] = '\0';
        } else {
            mode_[0] = '\0';
        }
    }
}

// конструктор с готовым FILE*
BaseFile::BaseFile(FILE* file) : file_(file) {
    if (file_) {
        // при использовании готового FILE* режим неизвестен
        mode_[0] = 'r';  // предполагаем чтение
        mode_[1] = '\0';
    } else {
        mode_[0] = '\0';
    }
}

// деструктор - закрываем файл
BaseFile::~BaseFile() {
    if (file_) {
        fclose(file_);
        file_ = nullptr;
    }
}

// проверка, открыт ли файл
bool BaseFile::is_open() const {
    return file_ != nullptr;
}

// проверка возможности чтения
bool BaseFile::can_read() const {
    if (!file_) return false;
    
    // проверяем режим открытия
    for (int i = 0; mode_[i]; i++) {
        if (mode_[i] == 'r' || mode_[i] == '+') {
            return true;
        }
    }
    return false;
}

// проверка возможности записи
bool BaseFile::can_write() const {
    if (!file_) return false;
    
    // проверяем режим открытия
    for (int i = 0; mode_[i]; i++) {
        if (mode_[i] == 'w' || mode_[i] == 'a' || mode_[i] == '+') {
            return true;
        }
    }
    return false;
}

// запись сырых данных в файл
size_t BaseFile::write_raw(const void* buf, size_t n_bytes) {
    if (!file_ || !buf || !can_write()) {
        return 0;
    }
    
    return fwrite(buf, 1, n_bytes, file_);
}

// чтение сырых данных из файла
size_t BaseFile::read_raw(void* buf, size_t max_bytes) {
    if (!file_ || !buf || !can_read()) {
        return 0;
    }
    
    return fread(buf, 1, max_bytes, file_);
}

// получение текущей позиции в файле
long BaseFile::tell() const {
    if (!file_) return -1L;
    return ftell(file_);
}

// установка позиции в файле
bool BaseFile::seek(long offset) {
    if (!file_) return false;
    return fseek(file_, offset, SEEK_SET) == 0;
}

// методы-обертки
size_t BaseFile::write(const void* buf, size_t n_bytes) {
    return write_raw(buf, n_bytes);
}

size_t BaseFile::read(void* buf, size_t max_bytes) {
    return read_raw(buf, max_bytes);
}