#include "boolarray.hpp"
#include <stdexcept>
#include <algorithm>

using namespace std;

void BoolArray::set_bit(size_t index, bool value) {
    size_t byte_idx = index / 8;
    size_t bit_idx = index % 8;
    
    if (value) {
        data_[byte_idx] |= (1 << bit_idx);
    } else {
        data_[byte_idx] &= ~(1 << bit_idx);
    }
}

bool BoolArray::get_bit(size_t index) const {
    size_t byte_idx = index / 8;
    size_t bit_idx = index % 8;
    // проверяем, установлен ли бит
    return (data_[byte_idx] & (1 << bit_idx)) != 0;
}

BoolArray::BoolArray(size_t size, bool default_value) : size_(size) {
    capacity_ = bytes_needed(size);
    data_ = new uint8_t[capacity_];
    
    uint8_t fill = default_value ? 0xFF : 0x00;
    for (size_t i = 0; i < capacity_; ++i) {
        data_[i] = fill;
    }
}

BoolArray::BoolArray(const BoolArray& other) : size_(other.size_), capacity_(other.capacity_) {
    data_ = new uint8_t[capacity_];
    for (size_t i = 0; i < capacity_; ++i) {
        data_[i] = other.data_[i];
    }
}


BoolArray::~BoolArray() {
    delete[] data_;
}


BoolArray& BoolArray::operator=(const BoolArray& other) {
    if (this != &other) {
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = new uint8_t[capacity_];
        for (size_t i = 0; i < capacity_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}


BoolArray::BitProxy BoolArray::operator[](size_t index) {
    if (index >= size_) throw out_of_range("Индекс выходит за границы массива");
    return BitProxy(*this, index);
}


bool BoolArray::operator[](size_t index) const {
    if (index >= size_) throw out_of_range("Индекс выходит за границы массива");
    return get_bit(index);
}

// Изменение размера
void BoolArray::resize(size_t new_size, bool fill_value) {
    if (new_size == size_) return;

    size_t new_capacity = bytes_needed(new_size);
    uint8_t* new_data = new uint8_t[new_capacity];
    uint8_t fill = fill_value ? 0xFF : 0x00;

    for (size_t i = 0; i < new_capacity; ++i) {
        new_data[i] = fill;
    }

    // копируем старые данные
    size_t min_capacity = min(capacity_, new_capacity);
    for (size_t i = 0; i < min_capacity; ++i) {
        new_data[i] = data_[i];
    }

    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;

    // если размер увеличился, то аккуратно инициализируем новые биты
    if (new_size > size_) {
        for (size_t i = size_; i < new_size; ++i) {
            set_bit(i, fill_value);
        }
    }
    
    size_ = new_size;
}