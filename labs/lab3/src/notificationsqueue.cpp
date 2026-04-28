#include "notificationsqueue.hpp"

// конструктор очереди
NotificationQueue::NotificationQueue() 
    : data_(nullptr), head_(0), tail_(0), size_(0), capacity_(0) {}

NotificationQueue::~NotificationQueue() {
    if (data_) {
        for (size_t i = 0; i < size_; ++i) {
            delete data_[(head_ + i) % capacity_];
        }
        delete[] data_;
    }
}

void NotificationQueue::push(Notification* n) {
    if (size_ == capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 4 : capacity_ * 2;
        Notification** new_data = new Notification*[new_capacity];
        
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[(head_ + i) % capacity_];
        }
        
        delete[] data_;
        data_ = new_data;
        head_ = 0;
        tail_ = size_;
        capacity_ = new_capacity;
    }
    
    data_[tail_] = n;
    tail_ = (tail_ + 1) % capacity_;
    size_++;
}

Notification* NotificationQueue::pop() {
    if (size_ == 0) return nullptr;
    
    Notification* n = data_[head_];
    head_ = (head_ + 1) % capacity_;
    size_--;
    return n;
}

size_t NotificationQueue::size() const {
    return size_;
}