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
        bool occupied = false;
    };

    Entry* table_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

    size_t hash(const char* s) const;
    void rehash();

public:
    WorkerDb();
    ~WorkerDb();

    WorkerData& operator[](const char* surname);

    class Iterator {
    private:
        Entry* current;
        Entry* end;
    public:
        Iterator(Entry* curr, Entry* last);
        Iterator& operator++();
        bool operator!=(const Iterator& other) const;
        WorkerData& operator*() const;
        WorkerData* operator->() const;
        const MyString& key() const;
    };

    Iterator begin();
    Iterator end();
};

#endif