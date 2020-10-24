#include "Deque.hpp"

// Constructor
Deque::Deque() : D(), n(0) {}

// Mantainance size and empty functions
int Deque::size() const {
    return n;
}

bool Deque::empty() const {
    return D.empty();
}

// Return element in front and back
const E& Deque::front() const {
    if (empty()) throw ("Error calling front(): Deque is empty.");
    return D.front();
}

const E& Deque::back() const {
    if (empty()) throw ("Error calling back(): Deque is empty");
    return D.back();
}

// Insert and remove elements from front and back.
void Deque::insertFront(const E& e) {
    D.addFront(e);
    n++;
}

void Deque::insertBack(const E& e) {
    D.addBack(e);
    n++;
}

void Deque::removeFront() {
    if (empty()) throw ("Error calling removeFront(): Deque is empty");
    D.removeFront();
    n--;
}

void Deque::removeBack() {
    if (empty()) throw ("Error calling removeBack(): Deque is empty");
    D.removeBack();
    n--;
}