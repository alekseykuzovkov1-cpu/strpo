#ifndef NOTIFICATION_QUEUE_HPP
#define NOTIFICATION_QUEUE_HPP

#include "notifications_oop.hpp"

class NotificationQueue {
private:
    Notification** data_;
    size_t head_;
    size_t tail_;
    size_t size_;
    size_t capacity_;

public:
    NotificationQueue();
    ~NotificationQueue();

    void push(Notification* n);
    Notification* pop();
    size_t size() const;

    class Iterator {
    private:
        Notification** data_ptr;
        size_t current_idx;
        size_t count;
        size_t cap;
    public:
        Iterator(Notification** d, size_t idx, size_t c, size_t cp) 
            : data_ptr(d), current_idx(idx), count(c), cap(cp) {}

        Notification* operator*() { return data_ptr[current_idx]; }
        Notification* operator->() { return data_ptr[current_idx]; }
        
        Iterator& operator++() {
            current_idx = (current_idx + 1) % cap;
            count++;
            return *this;
        }

        bool operator!=(const Iterator& other) const { return count != other.count; }
    };

    Iterator begin() { return Iterator(data_, head_, 0, capacity_); }
    Iterator end() { return Iterator(data_, tail_, size_, capacity_); }
};

#endif