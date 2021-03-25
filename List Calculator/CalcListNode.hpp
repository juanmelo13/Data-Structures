#ifndef CALC_LIST_NODE_H
#define CALC_LIST_NODE_H

#include <string>
using namespace std;

// Enum that contains all the arithmetic functions needed for newOperation
typedef enum { ADDITION, SUBTRACTION, MULTIPLICATION, DIVISION } FUNCTIONS;

class CalcListNode {
private:
    double total;
    FUNCTIONS oper;
    string operatorString;
    double operand;
    CalcListNode* next;
    friend class CalcList;
};

#endif