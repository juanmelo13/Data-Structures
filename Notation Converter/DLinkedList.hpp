#ifndef D_LINKED_LIST_H
#define D_LINKED_LIST_H

#include "DNode.hpp"

//This is a template class for a Doubly Linked List. Written by Juan Melo.

class DLinkedList {
public:
    DLinkedList();
    ~DLinkedList();
    bool empty() const;
    const E& front() const;
    const E& back() const;
    void addFront(const E& e);
    void addBack(const E& e);
    void removeFront();
    void removeBack();
private:
    DNode* header;
    DNode* trailer;
protected:
    void add(DNode* n, const E& e);
    void remove(DNode* n);
};

#endif