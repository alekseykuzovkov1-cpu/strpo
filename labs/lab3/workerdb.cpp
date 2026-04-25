#include "workerdb.hpp"
#include <utility>

WorkerDb::~WorkerDb() {
    delete[] data_;
}

WorkerData& WorkerDb::operator[](const char* surname) {
    for (size_t i = 0; i < size_; ++i) {
        if (data_[i].surname == surname) {
            return data_[i].data;
        }
    }

    Entry* new_data = new Entry[size_ + 1];

    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = std::move(data_[i]);
    }
    new_data[size_].surname = surname;
    
    delete[] data_;
    data_ = new_data;
    size_++;

    return data_[size_ - 1].data;
}