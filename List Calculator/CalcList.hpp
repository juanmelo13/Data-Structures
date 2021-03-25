#ifndef CALC_LIST_H
#define CALC_LIST_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include "CalcListNode.hpp"

using namespace std;

class CalcList {
public:
    CalcList();
    ~CalcList();
    double total() const;
    void newOperation(const FUNCTIONS func, const double operand);
    void removeLastOperation();
    std::string toString(unsigned short precision) const;
private:
    CalcListNode* head;
    int operations;
};

#endif