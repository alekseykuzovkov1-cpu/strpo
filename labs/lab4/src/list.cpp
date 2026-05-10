#include "list.hpp"
#include <iostream>

List::List() : m_size(0) {
    Head.pNext = &Tail;
    Tail.pPrev = &Head;
}

List::List(const List& other) : List() {
    Node* curr = other.Head.pNext;
    while (curr != &other.Tail) {
        push_back(curr->m_Data);
        curr = curr->pNext;
    }
}

List& List::operator=(const List& other) {
    if (this != &other) {
        List temp(other);
        std::swap(m_size, temp.m_size);
        std::swap(Head.pNext, temp.Head.pNext);
        std::swap(Tail.pPrev, temp.Tail.pPrev);
        
        Head.pNext->pPrev = &Head;
        Tail.pPrev->pNext = &Tail;
        
    }
    return *this;
}

List::~List() {
    clear();
}

void List::push_front(const Circle& c) {
    new Node(&Head, Head.pNext, &c);
    m_size++;
}

void List::push_back(const Circle& c) {
    new Node(Tail.pPrev, &Tail, &c);
    m_size++;
}

bool List::remove_first(const Circle& c) {
    Node* current = Head.pNext;
    while (current != &Tail) {
        if (current->m_Data == c) {
            delete current;
            m_size--;
            return true;
        }
        current = current->pNext;
    }
    return false;
}

size_t List::remove_all(const Circle& c) {
    size_t count = 0;
    Node* current = Head.pNext;
    while (current != &Tail) {
        Node* nextNode = current->pNext;
        
        if (current->m_Data == c) {
            delete current;
            m_size--;
            count++;
        }
        current = nextNode;
    }
    return count;
}

void List::clear() {
    while (Head.pNext != &Tail) {
        delete Head.pNext; 
    }
    m_size = 0;
}

void List::pop_front() {
    if (!empty()) {
        delete Head.pNext;
        m_size--;
    }
}

void List::pop_back() {
    if (!empty()) {
        delete Tail.pPrev;
        m_size--;
    }
}

void List::print() const {
    std::cout << "Список (размер " << m_size << "):" << std::endl;
    Node* current = Head.pNext;
    while (current != &Tail) {
        current->m_Data.print();
        std::cout << std::endl;
        current = current->pNext;
    }
}


void List::sort() {
    if (m_size < 2) return;

    Node* firstNode = Head.pNext;
    Tail.pPrev->pNext = nullptr; 
    firstNode->pPrev = nullptr;

    Node* sortedHead = mergeSort(firstNode);

    Head.pNext = sortedHead;
    sortedHead->pPrev = &Head;

    Node* curr = sortedHead;
    while (curr->pNext != nullptr) {
        curr = curr->pNext;
    }
    
    curr->pNext = &Tail;
    Tail.pPrev = curr;
}

List::Node* List::mergeSort(Node* head) {
    if (!head || !head->pNext) return head;

    Node* second = split(head);

    head = mergeSort(head);
    second = mergeSort(second);

    return merge(head, second);
}

List::Node* List::split(Node* head) {
    Node* fast = head;
    Node* slow = head;
    while (fast->pNext && fast->pNext->pNext) {
        fast = fast->pNext->pNext;
        slow = slow->pNext;
    }
    Node* temp = slow->pNext;
    slow->pNext = nullptr;
    if (temp) temp->pPrev = nullptr;
    return temp;
}

List::Node* List::merge(Node* first, Node* second) {
    if (!first) return second;
    if (!second) return first;

    if (first->m_Data.getArea() <= second->m_Data.getArea()) {
        first->pNext = merge(first->pNext, second);
        if (first->pNext) first->pNext->pPrev = first;
        first->pPrev = nullptr;
        return first;
    } else {
        second->pNext = merge(first, second->pNext);
        if (second->pNext) second->pNext->pPrev = second;
        second->pPrev = nullptr;
        return second;
    }
}

std::ostream& operator<<(std::ostream& os, const List& list) {
    List::Node* current = list.Head.pNext;
    while (current != &list.Tail) {
        os << current->m_Data << "\n";
        current = current->pNext;
    }
    return os;
}

std::istream& operator>>(std::istream& is, List& l) {
    Circle temp;
    while (is >> temp) {
        l.push_back(temp);
        is >> std::ws; 
    }
    return is;
}