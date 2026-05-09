#ifndef NOTIFICATION_PRIORITY_QUEUE_HPP
#define NOTIFICATION_PRIORITY_QUEUE_HPP

#include "notifications_oop.hpp"

class NotificationPriorityQueue {
private:
    Notification** data_;
    size_t size_;
    size_t capacity_;

    void siftUp(size_t index);
    void siftDown(size_t index);
    bool isHigherPriority(Notification* newNotif, Notification* existingNotif);

public:
    NotificationPriorityQueue();
    ~NotificationPriorityQueue();

    void push(Notification* n);
    Notification* pop();
    size_t size() const;

    class Iterator {
    private:
        Notification** ptr;
    public:
        Iterator(Notification** p) : ptr(p) {}
        Notification* operator*() { return *ptr; }
        Iterator& operator++() { ptr++; return *this; }
        bool operator!=(const Iterator& other) const { return ptr != other.ptr; }
    };

    Iterator begin() { return Iterator(data_); }
    Iterator end() { return Iterator(data_ + size_); }
};

#endif