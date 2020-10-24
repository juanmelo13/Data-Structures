#ifndef NOTATION_CONVERTER_H
#define NOTATION_CONVERTER_H

#include <cctype>
#include "NotationConverterInterface.hpp"
#include "Deque.hpp"

class NotationConverter : public NotationConverterInterface {
public:
    string postfixToInfix(string inStr);
    string postfixToPrefix(string inStr);
    
    string infixToPostfix(string inStr);
    string infixToPrefix(string inStr);

    string prefixToInfix(string inStr);
    string prefixToPostfix(string inStr);
protected: // Functions used by the public functions
    char const charType(char& c);
    int const precedence(string c);
};

#endif