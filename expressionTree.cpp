#include "expressionTree.h"
#include <string>
#include <sstream>
#include <iostream>
#include <stack>
#include <vector>
#include <cmath>

expressionTree::expressionTree() {
    this->root = nullptr;
}

expressionTree::expressionTree(std::string expr){
    this->root = nullptr;
    this->expression = expr;
}

expressionTreeNode* expressionTree::buildTypeOne() {
     return this->constructExpressionTree(this->expression);
}

unsigned long expressionTree::calculate() {
    return this->calculateHelper(this->root);
}

expressionTree::~expressionTree() {
    this->deleteHelper(this->root);
}

void expressionTree::deleteHelper(expressionTreeNode *current) {
    if(current == nullptr){
        return;
    }
    deleteHelper(current->left);
    deleteHelper(current->right);
    delete current;
}

unsigned long expressionTree::calcValue(unsigned long firstNum, unsigned long secondNum, char operation) {
    if(operation == '+'){
        return firstNum + secondNum;
    }else if(operation == '-'){
        return firstNum - secondNum;
    }else if(operation == '*'){
        return firstNum * secondNum;
    }else if(operation == '/'){
        return firstNum / secondNum;
    }else if(operation == '%'){
        return firstNum % secondNum;
    }
    return -1;
}

expressionTreeNode *expressionTree::constructExpressionTree(const std::string &expr) {
    std::stringstream str(expr);
    return constructExpressionTreeHelper(str);
}

expressionTreeNode *expressionTree::constructExpressionTreeHelper(std::stringstream &str) {
    std::string savenum = "";
    std::string operation;

    if(this->isDigit(this->asciiToDigit(str.peek()))){
        savenum = this->calculateNumber(str);
        if(str.peek()==-1){
            this->root = new expressionTreeNode(savenum);
            return this->root;
        }
    }else{
        //error
    }

    if(this->isValidOperation(this->asciiToOperation(str.peek()))){
        operation = this->charToString(str.peek());
        str.get();
    }else{
        //error
    }

    this->root = new expressionTreeNode(operation);
    expressionTreeNode* saveRoot = this->root;
    this->root->left = new expressionTreeNode(savenum);

    while(str.peek()!=-1) {
        if (this->isDigit(this->asciiToDigit(str.peek()))) {
            savenum = this->calculateNumber(str);
            if (str.peek() == -1) {
                if (this->root->right == nullptr) {
                    this->root->right = new expressionTreeNode(savenum);
                } else {
                    this->root->left = new expressionTreeNode(savenum);
                }
            }
        }else {
            //expected number
        }if(this->isValidOperation(this->asciiToOperation(str.peek()))){
            operation = this->charToString(str.peek());
            str.get();
            if(operation == "+" || operation == "-"){
                this->root->right = new expressionTreeNode(savenum);
                expressionTreeNode* newNode = new expressionTreeNode(operation);
                newNode->left = saveRoot;
                this->root = newNode;
                saveRoot=newNode;
            }else{
                this->root->right = new expressionTreeNode(operation);
                this->root=this->root->right;
                this->root->left = new expressionTreeNode(savenum);
            }
        }else{
            //invalid oper
        }
    }

    this->root = saveRoot;

    return this->root;
}

const bool expressionTree::isNumber(std::string s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

const bool expressionTree::isDigit(char c) {
    return c >= '0' && c<= '9';
}

const bool expressionTree::hasOnlyDigits(std::string s) {
    for(int i = 0; i<s.length(); ++i){
        if(s[i]<'0' || s[i]>'9'){
            return false;
        }
    }
    return true;
}

const int expressionTree::charToDigit(const char s) {
    switch(s){
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
    }

}

const char expressionTree::asciiToDigit(const int x) {
    switch(x){
        case 48: return '0';
        case 49: return '1';
        case 50: return '2';
        case 51: return '3';
        case 52: return '4';
        case 53: return '5';
        case 54: return '6';
        case 55: return '7';
        case 56: return '8';
        case 57: return '9';
    }
}

const bool expressionTree::isValidOperation(char s) {
    return s=='+' || s=='-' || s=='*' || s=='/' || s=='%';
}

const char expressionTree::asciiToOperation(const int x) {
    switch(x) {
        case 42: return '*';
        case 43: return '+';
        case 45: return '-';
        case 47: return '/';
        case 37: return '%';
    }
}

std::string expressionTree::calculateNumber(std::stringstream &str) {
    std::stack<int> s;
    int result = 0;

    while(this->isDigit(this->asciiToDigit(str.peek()))){
        s.push(charToDigit(str.peek()));
        str.get();
    }

    const int saveSize = s.size();

    for(int i = 0; i < saveSize; ++i){
        result+=pow(10, i)*s.top();
        s.pop();
    }

    std::stringstream ss;
    ss << result;
    std::string convertedNumberToString = ss.str();
    return convertedNumberToString;
}

std::string expressionTree::charToString(char c) {
    std::string operation(1, c);
    return operation;
}

void expressionTree::printH(expressionTreeNode *current) {
    if(current == nullptr){
        return;
    }
    printH(current->left);
    std::cout << current->data << std::endl;
    printH(current->right);
}

void expressionTree::print() {
    this->printH(this->root);
}

const int expressionTree::countLeavesHelper(expressionTreeNode *current) {
    if(current == nullptr){
        return 0;
    }
    if(current->left == nullptr && current->right==nullptr){
        return 1;
    }
    return countLeavesHelper(current->left) + countLeavesHelper(current->right);
}

const int expressionTree::countLeaves() {
    return this->countLeavesHelper(this->root);
}

void expressionTree::setExpression(std::string s) {
    this->expression = s;
}

unsigned long expressionTree::apply(std::string operation, int num1, int num2) {
    switch(this->stringToChar(operation)){
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num1 / num2;
        case '%': return num1 % num2;
    }
    return -1;
}

const int expressionTree::stringToNumber(std::string s) {
    int result = 0;
    for(int i = 0; i < s.length(); ++i){
        result+=charToDigit(s[i])*pow(10, s.length()-i-1);
    }
    return result;
}

const char expressionTree::stringToChar(std::string s) {
    if(s=="+"){
        return '+';
    }else if(s=="-"){
        return '-';
    }else if(s=="*"){
        return '*';
    }else if(s=="/"){
        return '/';
    }else{
        return '%';
    }
}

unsigned long expressionTree::calculateHelper(expressionTreeNode *current) {
    if(current->left == nullptr && current->right == nullptr && this->isDigit(current->data)){
        return this->stringToNumber(current->data);
    }
    if(current->data!="!"){
        unsigned long leftValue = calculateHelper(current->left);
        unsigned long rightValue = calculateHelper(current->right);

        return this->apply(current->data, leftValue, rightValue);
    }
}

const bool expressionTree::isDigit(std::string s) {
    for(int i = 0; i < s.length(); ++i){
        if(s[i]<'0' || s[i]>'9'){
            return false;
        }
    }
    return true;
}
