#ifndef LIST_HPP
#define LIST_HPP

#include "circle.hpp"
#include "iostream"

class List {
private:
    struct Node {
    Node* pPrev;
    Node* pNext;
    Circle m_Data;

    Node() : pPrev(nullptr), pNext(nullptr), m_Data(0, 0, 0) {}

    Node(Node* prev, Node* next, const Circle* pc) 
        : pPrev(prev), pNext(next), m_Data(*pc) 
    {
        if (pPrev) pPrev->pNext = this;
        if (pNext) pNext->pPrev = this;
    }
    
    ~Node() {
        if (pPrev) pPrev->pNext = pNext;
        if (pNext) pNext->pPrev = pPrev;
    }
    };

    Node Head;
    Node Tail;
    size_t m_size;

    Node* mergeSort(Node* head);
    Node* merge(Node* first, Node* second);
    Node* split(Node* head);

public:
    List();
    ~List();

    List(const List& other);
    List& operator=(const List& other);

    void push_front(const Circle& c);
    void push_back(const Circle& c);
    bool remove_first(const Circle& c);
    size_t remove_all(const Circle& c);
    void clear();

    void pop_front();
    void pop_back();
    void print() const;
    size_t size() const { return m_size; }
    bool empty() const { return m_size == 0; }

    void sort();

    friend std::ostream& operator<<(std::ostream& os, const List& list);
    friend std::istream& operator>>(std::istream& is, List& list);
};

#endif