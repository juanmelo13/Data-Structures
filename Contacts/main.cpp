#include <iostream>
using namespace std;

#include "ContactNode.h"

int main() {
    string tempName, tempPhone;
    ContactNode* head = new ContactNode();

    //First Person
    cout << "Person 1\n";
    cout << "Enter name:\n";
    getline(cin, tempName);
    cout << "Enter phone number:\n";
    getline(cin, tempPhone);
    cout << "You entered: " << tempName << ", " << tempPhone << endl;
    cout << endl;

    ContactNode* first = new ContactNode(tempName, tempPhone);
    head->InsertAfter(first);

    //Second Person
    cout << "Person 2\n";
    cout << "Enter name:\n";
    getline(cin, tempName);
    cout << "Enter phone number:\n";
    getline(cin, tempPhone);
    cout << "You entered: " << tempName << ", " << tempPhone << endl;
    cout << endl;

    ContactNode* second = new ContactNode(tempName, tempPhone);
    first->InsertAfter(second);

    //Third Person
    cout << "Person 3\n";
    cout << "Enter name:\n";
    getline(cin, tempName);
    cout << "Enter phone number:\n";
    getline(cin, tempPhone);
    cout << "You entered: " << tempName << ", " << tempPhone << endl;
    cout << endl;

    ContactNode* third = new ContactNode(tempName, tempPhone);
    second->InsertAfter(third);

    //Print
    ContactNode* current = first;
    cout << "CONTACT LIST\n";
    while(current != nullptr) {
        current->PrintContactNode();
        cout << endl;
        current = current->GetNext();
    }

    return 0;
}
