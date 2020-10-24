#include "DLinkedList.hpp"

// Constructor and destructor
DLinkedList::DLinkedList() {
    header = new DNode;
    trailer = new DNode;
    header->next = trailer;
    trailer->prev = header;
}

DLinkedList::~DLinkedList() {
    while (!empty()) removeFront();
    delete trailer;
    delete header;
}

// Is the List empty?
bool DLinkedList::empty() const {
    return (header->next == trailer);
}

// Return the element in front and back
const E& DLinkedList::front() const {
    if(empty()) throw ("Empty List");
    return header->next->elem;
}

const E& DLinkedList::back() const {
    if(empty()) throw ("Empty List");
    return trailer->prev->elem;
}

// Add new nodes
void DLinkedList::add(DNode* n, const E& e) {
    DNode* t = new DNode;
    t->elem = e;
    t->next = n;
    t->prev = n->prev;
    n->prev->next = t;
    n->prev = t;

}

void DLinkedList::addFront(const E& e) {
    add(header->next, e);
}

void DLinkedList::addBack(const E& e) {
    add(trailer, e);
}

// Remove nodes
void DLinkedList::remove(DNode* n) {
    DNode* prev = n->prev;
    DNode* next = n->next;
    prev->next = next;
    next->prev = prev;
    delete n;
}

void DLinkedList::removeFront() {
    remove(header->next);
}

void DLinkedList::removeBack() {
    remove(trailer->prev);
}