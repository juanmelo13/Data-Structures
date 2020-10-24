#include "NotationConverter.hpp"

// Check for the character type and its precedence
char const NotationConverter::charType(char& c) {
    if (isalpha(c)) return 'c';
    else if (c == '+' || c == '-' || c == '*' || c == '/') return 'o';
    else if (c == ' ') return 's';
    else if (c == '(' || c == ')') return c;
    else return 'I';
}

int const NotationConverter::precedence(string c) {
    if (c == "+" || c == "-") return 1;
    else if (c == "*" || c == "/") return 2;
    else return -1;
}

// Conversions from postfix
string NotationConverter::postfixToInfix(string inStr) {
    string operand1, operand2, operation;                   // String holders 
    char c;
    Deque d;

    // Scan inStr
    for (unsigned int i = 0; i < inStr.length(); i++) {
        c = inStr.at(i);
        switch (charType(c)) {
            case 'c':
                operation = c;
                d.insertFront(operation);
                break;
            case 'o':
                operand2 = d.front();
                d.removeFront();
                operand1 = d.front();
                d.removeFront();
                operation = c;
                operation = "(" + operand1 + " " + operation + " " + operand2 + ")";
                d.insertFront(operation);
                break;
            case 's':
                break;
            case 'I':
                throw ("Invalid character in input.");
        }
    }
    operation = d.front(); 
    return operation;
}

string NotationConverter::postfixToPrefix(string inStr) {
    string operand1, operand2, operation;                   // String holders 
    char c;
    Deque d;

    // Scan inStr
    for (unsigned int i = 0; i < inStr.length(); i++) {
        c = inStr.at(i);
        switch (charType(c)) {
            case 'c':
                operation = c;
                d.insertFront(operation);
                break;
            case 'o':
                operand2 = d.front();
                d.removeFront();
                operand1 = d.front();
                d.removeFront();
                operation = c;
                operation += " " + operand1 + " " + operand2;
                d.insertFront(operation);
                break;
            case 's':
                break;
            case 'I':
                throw ("Invalid character in input.");
        }
    }
    operation = d.front(); 
    return operation;
}

// Conversions from infix
string NotationConverter::infixToPostfix(string inStr) {
    string character, operation;                           // String holders 
    char c;
    Deque d;

    // Scan inStr
    for (unsigned int i = 0; i < inStr.length(); i++) {
        c = inStr.at(i);
        character = c;
        switch (charType(c)) {
            case 'c':
                operation += " " + character;
                break;
            case '(':
                d.insertFront(character);
                break;
            case ')':
                while (!d.empty() && d.front() != "(") {
                    operation += " " + d.front();
                    d.removeFront();
                }
                if (!d.empty() && d.front() == "(") d.removeFront();
                break;
            case 'o':
                while (!d.empty() && precedence(character) <= precedence(d.front())) { 
                    operation += " " + d.front();
                    d.removeFront();
                } 
                d.insertFront(character); 
                break;
            case 's':
                break;
            case 'I':
                throw ("Invalid character in input.");
        }
    }

    // Empty the rest of the deque into the operation
    while (!d.empty()) {
        operation += " " + d.front();
        d.removeFront();
    }

    return operation;
}

string NotationConverter::infixToPrefix(string inStr) {
    string container;

    // Convert first to postfix and then to prefix
    container = infixToPostfix(inStr);
    container = postfixToPrefix(container);
    return container;
}

// Conversions from prefix
string NotationConverter::prefixToInfix(string inStr) {
    string container;

    // Convert first to postfix and then to infix
    container = prefixToPostfix(inStr);
    container = postfixToInfix(container);
    return container;
}

string NotationConverter::prefixToPostfix(string inStr) {
    string operand1, operand2, operation, character;                   // String holders 
    char c;
    Deque d;
    int len = inStr.length() - 1;

    // Scan inStr
    for (int i = len; i >= 0; i--) {
        c = inStr.at(i);
        character = c;
        switch (charType(c)) {
            case 'c':
                d.insertFront(character);
                break;
            case 'o':
                operand1 = d.front();
                d.removeFront();
                operand2 = d.front();
                d.removeFront();
                operation = operand1 + " " + operand2 + " " + character;
                d.insertFront(operation);
                break;
            case 's':
                break;
            case 'I':
                throw ("Invalid character in input.");
        }
    }
    operation = d.front(); 
    return operation;
}