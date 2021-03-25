#include "ContactNode.h"

using namespace std;

ContactNode::ContactNode(string name, string phone, ContactNode* next) {
    this->name = name;
    this->phone = phone;
    this->next = next;
}

void ContactNode::InsertAfter(ContactNode* next) {
    ContactNode* tempNext = nullptr;

    tempNext = this->next;
    this->next = next;
    next->next = tempNext;
}

string ContactNode::GetName() const {
    return this->name;
}

string ContactNode::GetPhoneNumber() const {
    return this->phone;
}

ContactNode* ContactNode::GetNext() const {
    return next;
}

void ContactNode::PrintContactNode() const {
    cout << "Name: " << GetName() << endl;
    cout << "Phone number: " << GetPhoneNumber() << endl;
}