#ifndef D_NODE_H
#define D_NODE_H

#include <string>

using namespace std;

// This is a template class for a Doubly Linked Node, created by Juan Jose Melo.

typedef string E;
class DNode {
private:
    E elem;
    DNode* prev;
    DNode* next;
friend class DLinkedList;
};

#endif