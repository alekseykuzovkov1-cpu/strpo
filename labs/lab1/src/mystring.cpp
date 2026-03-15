#include "mystring.hpp"
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

// выделение памяти с заданной вместимостью
void MyString::allocate(size_t new_capacity) {
    data_ = new char[new_capacity + 1];  // +1 для '\0'
    capacity_ = new_capacity;
}

// освобождение памяти
void MyString::deallocate() {
    if (data_) {
        delete[] data_;
        data_ = nullptr;
    }
    size_ = 0;
    capacity_ = 0;
}

//гарантирование выделения памяти
void MyString::ensure_allocated() {
    if (!data_) {
        allocate(15);  // выделяем минимальный буфер при первом использовании
        data_[0] = '\0';
    }
}

// копирование строки
void MyString::copy_from(const char* str, size_t len) {
    ensure_allocated();
    if (str) {
        if (capacity_ < len) {
            deallocate();
            allocate(len);
        }
        
        memcpy(data_, str, len);
        data_[len] = '\0';
        size_ = len;
    }
}

// изменение размера выделенной памяти
void MyString::resize(size_t new_capacity) {
    ensure_allocated();
    if (new_capacity > capacity_) {
        char* new_data = new char[new_capacity + 1];
        if (data_) {
            memcpy(new_data, data_, size_ + 1);
            delete[] data_;
        }
        data_ = new_data;
        capacity_ = new_capacity;
    }
}

// пустая строка
MyString::MyString() 
    : data_(nullptr), size_(0), capacity_(0) {
    // TODO: сделать без выделения динамической памяти
    
    // выделяем минимальную память для пустой строки
}

MyString::MyString(const char* str) 
    : data_(nullptr), size_(0), capacity_(0) {
    if (str) {
        size_t len = strlen(str);
        allocate(len);
        copy_from(str, len);
    } else {
        allocate(15);
        data_[0] = '\0';
    }
}

MyString::MyString(const MyString& other) 
    : data_(nullptr), size_(0), capacity_(0) {
    allocate(other.capacity_);
    copy_from(other.data_, other.size_);
}

MyString::~MyString() {
    deallocate();
}

// оператор присваивания
MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        copy_from(other.data_, other.size_);
    } else {
        deallocate();
    }
    return *this;
}

// получение i-того элемента
char MyString::get(int i) const {
    if (i < 0 || static_cast<size_t>(i) >= size_) {
        throw out_of_range("Индекс выходит за границы строки");
    }
    return data_[i];
}

// установка i-того элемента
void MyString::set(int i, char c) {
    if (i < 0 || static_cast<size_t>(i) >= size_) {
        throw out_of_range("Индекс выходит за границы строки");
    }
    data_[i] = c;
}

// замена текущего содержимого на новое
void MyString::set_new_string(const char* str) {
    if (str) {
        size_t len = strlen(str);
        
        // если не хватает памяти, то перевыделяем
        if (capacity_ < len) {
            deallocate();
            allocate(len);
        }
        
        copy_from(str, len);
    } else {
        deallocate();
    }
}

// вывод строки на консоль
void MyString::print() const {
    if (data_) {
        cout << data_;
    }
}

// чтение строки с консоли (неопределенного размера)
void MyString::read_line() {
    const int BUFFER_SIZE = 128;
    char buffer[BUFFER_SIZE];
    size_t total_size = 0;
    
    deallocate();
    
    //читаем построчно, пока не встретим '\n'
    while (cin.getline(buffer, BUFFER_SIZE)) {
        size_t chunk_size = strlen(buffer);
        
        // проверяем, не закончился ли ввод
        if (chunk_size == 0 && cin.gcount() == 1) {
            break;
        }
        
        // перевыделяем память
        resize(total_size + chunk_size);
        
        // копируем новые данные
        memcpy(data_ + total_size, buffer, chunk_size);
        total_size += chunk_size;
        
        // проверяем, был ли это конец строки
        if (cin.gcount() < BUFFER_SIZE) {
            break;
        }
    }
    
    size_ = total_size;
    if (data_) {
        data_[size_] = '\0';
    }
    
    // очищаем флаги cin
    cin.clear();
}