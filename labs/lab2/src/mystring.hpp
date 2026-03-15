#include <cstddef>

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
    
    const char* c_str() const { return data_; }
};
#endif
