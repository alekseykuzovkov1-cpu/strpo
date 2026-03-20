#include "basefile.hpp"
#include <cstring>
#include <iostream>
using namespace std;

BaseFile::BaseFile() : file(nullptr), readable(false), writable(false) {
    cout << "[CONSTRUCTOR] BaseFile (default)" << endl;
}

BaseFile::BaseFile(const char* path, const char* mode) {
    cout << "[CONSTRUCTOR] BaseFile (path: " << path << ")" << endl;

    file = std::fopen(path, mode);
    
    // Инициализируем флаги ложью по умолчанию
    readable = false;
    writable = false;
    
    if (file) {
        // 'r' или '+' открывают доступ на чтение
        if (std::strchr(mode, 'r') || std::strchr(mode, '+')) {
            readable = true;
        }
        // 'w', 'a' или '+' открывают доступ на запись
        if (std::strchr(mode, 'w') || std::strchr(mode, 'a') || std::strchr(mode, '+')) {
            writable = true;
        }
    }
}

BaseFile::BaseFile(FILE* existing_file, bool r, bool w) 
    : file(existing_file), readable(r), writable(w) {
        cout << "[CONSTRUCTOR] BaseFile (from existing FILE*)" << endl;
    }

BaseFile::~BaseFile() {
    cout << "[DESTRUCTOR] BaseFile" << endl;

    if (file) {
        fclose(file);
        file = nullptr;
    }
}

bool BaseFile::is_open() const { 
    return file != nullptr; 
}

bool BaseFile::can_read() const { 
    return is_open() && readable; 
}

bool BaseFile::can_write() const { 
    return is_open() && writable; 
}

size_t BaseFile::write_raw(const void* buf, size_t n_bytes) {
    if (!can_write()) return 0;
    return fwrite(buf, 1, n_bytes, file);
}

size_t BaseFile::read_raw(void* buf, size_t max_bytes) {
    if (!can_read()) return 0;
    return fread(buf, 1, max_bytes, file);
}

size_t BaseFile::write(const void* buf, size_t n_bytes) {
    return write_raw(buf, n_bytes);
}

size_t BaseFile::read(void* buf, size_t max_bytes) {
    return read_raw(buf, max_bytes);
}

long BaseFile::tell() const {
    return is_open() ? ftell(file) : -1L;
}

bool BaseFile::seek(long offset) {
    if (!is_open()) return false;
    return fseek(file, offset, SEEK_SET) == 0;
}