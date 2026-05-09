#include "notifications_priority_queue.hpp"

NotificationPriorityQueue::NotificationPriorityQueue() 
    : data_(nullptr), size_(0), capacity_(0) {}

NotificationPriorityQueue::~NotificationPriorityQueue() {
    if (data_) {
        for (size_t i = 0; i < size_; ++i) {
            delete data_[i];
        }
        delete[] data_;
    }
}

bool NotificationPriorityQueue::isHigherPriority(Notification* newN, Notification* existN) {
    // срочное системное выше всех
    if (newN->getPriorityScore() == 0 && existN->getPriorityScore() != 0) return true;
    if (existN->getPriorityScore() == 0 && newN->getPriorityScore() != 0) return false;

    // если оба несрочные системные или оба срочные, то смотрим на время
    if (newN->getTimestamp() < existN->getTimestamp()) return true;
    if (newN->getTimestamp() > existN->getTimestamp()) return false;

    // если время совпало, смотрим на тип
    return newN->getPriorityScore() < existN->getPriorityScore();
}

void NotificationPriorityQueue::siftUp(size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (isHigherPriority(data_[index], data_[parent])) {
            Notification* temp = data_[index];
            data_[index] = data_[parent];
            data_[parent] = temp;
            index = parent;
        } else {
            break;
        }
    }
}

void NotificationPriorityQueue::siftDown(size_t index) {
    while (2 * index + 1 < size_) {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t largest = index;

        if (left < size_ && isHigherPriority(data_[left], data_[largest]))
            largest = left;
        if (right < size_ && isHigherPriority(data_[right], data_[largest]))
            largest = right;

        if (largest != index) {
            Notification* temp = data_[index];
            data_[index] = data_[largest];
            data_[largest] = temp;
            index = largest;
        } else {
            break;
        }
    }
}

void NotificationPriorityQueue::push(Notification* n) {
    if (size_ == capacity_) {
        size_t new_capacity = (capacity_ == 0) ? 4 : capacity_ * 2;
        Notification** new_data = new Notification*[new_capacity];
        for (size_t i = 0; i < size_; ++i) new_data[i] = data_[i];
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }
    data_[size_] = n;
    siftUp(size_);
    size_++;
}

Notification* NotificationPriorityQueue::pop() {
    if (size_ == 0) return nullptr;
    Notification* top = data_[0];
    data_[0] = data_[size_ - 1];
    size_--;
    if (size_ > 0) siftDown(0);
    return top;
}

size_t NotificationPriorityQueue::size() const { return size_; }