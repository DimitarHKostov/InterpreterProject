#ifndef PROJECTSDP_EXPRESSIONTREE_H
#define PROJECTSDP_EXPRESSIONTREE_H
#include "expressionTreeNode.h"
#include <string>

class expressionTree {
public:
    expressionTree();
    expressionTree(std::string);

    void setExpression(std::string);
    expressionTreeNode* buildTypeOne();
    unsigned long calculate();
    ~expressionTree();

    //da go iztriq printa
    void print();
private:
    expressionTreeNode* root;
    std::string expression;

    void deleteHelper(expressionTreeNode*);
    void printH(expressionTreeNode*);
    const bool isNumber(std::string);
    const bool isDigit(char);
    const bool isValidOperation(char);
    const bool hasOnlyDigits(std::string);
    const int countLeavesHelper(expressionTreeNode*);
    const int charToDigit(const char);
    const int stringToNumber(std::string);
    unsigned long apply(std::string, int, int);
    const char stringToChar(std::string);
    const int countLeaves();
    unsigned long calculateHelper(expressionTreeNode*);
    const bool isDigit(std::string);
    const char asciiToDigit(const int);
    const char asciiToOperation(const int);
    unsigned long calcValue(unsigned long, unsigned long, char);
    std::string charToString(char c);
    std::string calculateNumber(std::stringstream&);
    expressionTreeNode* constructExpressionTreeHelper(std::stringstream&);
    expressionTreeNode* constructExpressionTree(const std::string&);
};




#endif //PROJECTSDP_EXPRESSIONTREE_H
