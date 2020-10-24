#ifndef DEQUE_H
#define DEQUE_H

#include "DLinkedList.hpp"

// This is a template for a Deque class, implemented with a Doubly Linked List. Written by Juan Melo.

class Deque {
public:
    Deque();
    int size() const;
    bool empty() const;
    const E& front() const;
    const E& back() const;
    void insertFront(const E& e);
    void insertBack(const E& e);
    void removeFront();
    void removeBack();
private:
    DLinkedList D;
    int n;
};

#endif