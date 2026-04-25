#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <iostream>

#ifndef MYSTRING_HPP
#define MYSTRING_HPP

class MyString {
private:
    char* data_;        // указатель на динамическую память со строкой
    size_t size_;       // размер строки (без учета '\0')
    size_t capacity_;   // вместимость выделенной памяти
    
    void allocate(size_t new_capacity);
    void deallocate();
    void ensure_allocated();
    void copy_from(const char* str, size_t len);
    void resize(size_t new_capacity);
    
public:
    MyString();                             // пустая строка
    MyString(const char* str);
    MyString(const MyString& other);
    ~MyString();
    
    // оператор присваивания
    MyString& operator=(const MyString& other);
    
    char get(int i) const;
    void set(int i, char c);
    size_t length() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }
    
    // операции со строкой
    void set_new_string(const char* str);
    void print() const;
    void read_line();

    MyString& operator+=(const char* str);
    MyString& operator+=(const MyString& other);

    MyString(MyString&& other) noexcept;
    MyString& operator=(MyString&& other) noexcept;

    const char* c_str() const {
        return data_ ? data_ : "";
    }

    char& operator[](size_t index);
    const char& operator[](size_t index) const {
        if (index >= size_) throw std::out_of_range("...");
        return data_[index];
    }
};
MyString operator+(const MyString& lhs, const MyString& rhs);
MyString operator+(const MyString& lhs, const char* rhs);
MyString operator+(const char* lhs, const MyString& rhs);

inline bool operator==(const MyString& lhs, const MyString& rhs) {
    return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}
inline bool operator==(const MyString& lhs, const char* rhs) {
    return std::strcmp(lhs.c_str(), rhs) == 0;
}
inline bool operator==(const char* lhs, const MyString& rhs) {
    return std::strcmp(lhs, rhs.c_str()) == 0;
}


inline bool operator!=(const MyString& lhs, const MyString& rhs) { return !(lhs == rhs); }
inline bool operator!=(const MyString& lhs, const char* rhs) { return !(lhs == rhs); }
inline bool operator!=(const char* lhs, const MyString& rhs) { return !(lhs == rhs); }


inline bool operator<(const MyString& lhs, const MyString& rhs) {
    return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
}
inline bool operator<(const MyString& lhs, const char* rhs) {
    return std::strcmp(lhs.c_str(), rhs) < 0;
}
inline bool operator<(const char* lhs, const MyString& rhs) {
    return std::strcmp(lhs, rhs.c_str()) < 0;
}


inline bool operator<=(const MyString& lhs, const MyString& rhs) {
    return std::strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}
inline bool operator<=(const MyString& lhs, const char* rhs) {
    return std::strcmp(lhs.c_str(), rhs) <= 0;
}
inline bool operator<=(const char* lhs, const MyString& rhs) {
    return std::strcmp(lhs, rhs.c_str()) <= 0;
}

std::ostream& operator<<(std::ostream& os, const MyString& str);
std::istream& operator>>(std::istream& is, MyString& str);
#endif
