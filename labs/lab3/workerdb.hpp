#ifndef WORKERDB_HPP
#define WORKERDB_HPP

#include "mystring.hpp"

struct WorkerData {
    MyString name;
    int age;

    WorkerData() : name(""), age(0) {}
    WorkerData(const char* n, int a) : name(n), age(a) {}
};

class WorkerDb {
private:
    struct Entry {
        MyString surname;
        WorkerData data;
    };

    Entry* data_ = nullptr;
    size_t size_ = 0;

public:
    WorkerDb() : data_(nullptr), size_(0) {}

    ~WorkerDb();

    class Iterator {
    private:
        Entry* ptr; // указатель на текущую запись
    public:
        Iterator(Entry* p) : ptr(p) {}

        Iterator& operator++() {
            ptr++;
            return *this;
        }

        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
        bool operator==(const Iterator& other) const { return ptr == other.ptr; }

        WorkerData& operator*() const { return ptr->data; }

        WorkerData* operator->() const { return &(ptr->data); }

        const MyString& key() const { return ptr->surname; }
    };

    Iterator begin() { return Iterator(data_); }
    Iterator end() { return Iterator(data_ + size_); }

    WorkerData& operator[](const char* surname);

    WorkerDb(const WorkerDb&) = delete;
    WorkerDb& operator=(const WorkerDb&) = delete;
};

#endif