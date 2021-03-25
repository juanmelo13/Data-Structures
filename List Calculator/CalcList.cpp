#include "CalcList.hpp"

CalcList::CalcList() : head(NULL) { }

double CalcList::total() const {
    if (head == NULL)
        return 0.0;
    else
        return head->total;
}

void CalcList::newOperation(const FUNCTIONS func, const double operand) {
    CalcListNode* newNode = new CalcListNode;
    newNode->oper = func;
    newNode->operand = operand;

    switch (func)
    {
    case ADDITION:
        newNode->operatorString = "+";
        newNode->total = total() + operand;
        break;
    case SUBTRACTION:
        newNode->operatorString = "-";
        newNode->total = total() - operand;
        break;
    case MULTIPLICATION:
        newNode->operatorString = "*";
        newNode->total = total() * operand;
        break;
    case DIVISION:
        if (operand == 0.0)
            throw runtime_error("Math error: Attempted to divide by Zero\n");
        newNode->operatorString = "/";
        newNode->total = total() / operand;    
    default:
        return;
    }

    newNode->next = head;
    head = newNode;
    operations++;
}

void CalcList::removeLastOperation() {
    CalcListNode* oldHead = head;
    head = oldHead->next;
    delete(oldHead);
    operations--;
}

string CalcList::toString(unsigned short precision) const {
    ostringstream buffer;
    CalcListNode* curr = head;
    int index = operations;

    while(curr->next != NULL) {
        buffer << setprecision(precision) << index << ": " << curr->next->total;
        buffer << curr->operatorString << curr->operand << "=" << curr->total << "\n";
    }

    return buffer.str();
}

CalcList::~CalcList() {
    while (head != NULL) {
        removeLastOperation();
    }
}