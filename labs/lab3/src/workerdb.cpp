#include "workerdb.hpp"
#include <utility>

WorkerDb::WorkerDb() : table_(nullptr), size_(0), capacity_(0) {}

WorkerDb::~WorkerDb() {
    delete[] table_;
}

size_t WorkerDb::hash(const char* s) const {
    size_t h = 5381;
    int c;
    while ((c = *s++))
        h = ((h << 5) + h) + c;
    return h;
}

void WorkerDb::rehash() {
    size_t old_capacity = capacity_;
    Entry* old_table = table_;

    capacity_ = (capacity_ == 0) ? 8 : capacity_ * 2;
    table_ = new Entry[capacity_];
    size_ = 0;

    for (size_t i = 0; i < old_capacity; ++i) {
        if (old_table[i].occupied) {
            (*this)[old_table[i].surname.c_str()] = old_table[i].data;
        }
    }
    delete[] old_table;
}

WorkerData& WorkerDb::operator[](const char* surname) {
    if (capacity_ == 0 || (double)size_ / capacity_ > 0.7) {
        rehash();
    }

    size_t h = hash(surname);
    size_t idx = h % capacity_;

    while (table_[idx].occupied) {
        if (table_[idx].surname == surname) {
            return table_[idx].data;
        }
        idx = (idx + 1) % capacity_;
    }

    table_[idx].surname = surname;
    table_[idx].occupied = true;
    size_++;
    return table_[idx].data;
}

WorkerDb::Iterator::Iterator(Entry* curr, Entry* last) : current(curr), end(last) {
    while (current < end && !current->occupied) {
        current++;
    }
}

WorkerDb::Iterator& WorkerDb::Iterator::operator++() {
    do {
        current++;
    } while (current < end && !current->occupied);
    return *this;
}

bool WorkerDb::Iterator::operator!=(const Iterator& other) const {
    return current != other.current;
}

WorkerData& WorkerDb::Iterator::operator*() const {
    return current->data;
}

WorkerData* WorkerDb::Iterator::operator->() const {
    return &(current->data);
}

const MyString& WorkerDb::Iterator::key() const {
    return current->surname;
}


WorkerDb::Iterator WorkerDb::begin() { 
    return Iterator(table_, table_ + capacity_); 
}

WorkerDb::Iterator WorkerDb::end() { 
    return Iterator(table_ + capacity_, table_ + capacity_); 
}