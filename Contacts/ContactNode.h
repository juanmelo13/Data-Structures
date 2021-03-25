#ifndef CONTACT_NODE_H
#define CONTACT_NODE_H

#include <string>
#include <iostream>
using namespace std;

class ContactNode {
    private:
        string name;
        string phone;
        ContactNode* next;
    public:
        ContactNode(string name = "VOID", string phone = "VOID", ContactNode* next = nullptr);
        void InsertAfter(ContactNode* next);
        string GetName() const;
        string GetPhoneNumber() const;
        ContactNode* GetNext() const;
        void PrintContactNode() const;
};

#endif