#ifndef PROJECTSDP_INTERPRETATOR_H
#define PROJECTSDP_INTERPRETATOR_H
#include "Line.h"
#include "textContainer.h"
#include "FunctionContainer.h"
#include "errorContainer.h"
#include "expressionTree.h"
#include <vector>
#include <string>

class Interpreter {
public:
    void push();
    Interpreter();
    void interpret(std::string);
    ~Interpreter();
private:
    textContainer text;
    FunctionContainer funcBox;
    Container box;
    errorContainer errors;
    expressionTree tree;

    void printBracketsHelper(Line&, const int);

    void bracketTreeExpression(Line&);
    std::string getBracketCaseVarName(Line&);
    std::string getBracketCaseFunctionName(Line&);
    std::string getBracketCaseExpression(Line&);

    std::string replace(std::string, std::string, std::string);
    const std::string killWhiteSpacesFromBehind(std::string);
    std::string sbb(std::string);
    void printHelper(Line&, const int);
    void printManipulator(Line&, const int);
    void readHelper(std::istream&, Line&, const int);
    void setVariableAndValue(Line&, const int);
    void treeManipulator(Line&, const int);
    std::string insideHelper(std::string);
    std::string treeExpressionConverter(std::string);
    std::string bracketTreeExpressionConverter(std::string);
    const bool containsBrackets(Line&) const;
    const bool containsLetters(std::string);
    const bool containsEquals(Line&) const;
    const bool containsSpace(std::string) const;
    const bool containsMoreThanOneEquals(Line&) const;
    const bool isPrint(Line&) const;
    const bool isRead(Line&) const;
    const std::string variableSetterHelper(Line&, const int);
    const std::string buildTreeFrom(Line&);
    Line& killwhitespaces(Line&);
    Line& printVariable(Line&);
    Line& readVariable(Line&);
    const Line& killwst(Line&);
    const int numOfEquals(Line&);
    std::string UnsignedLongToString(unsigned long&);
    void toInterpret(std::string);
    const bool isVarType(std::string) const;
    std::string removeLetters(std::string);
    const bool isFunType(std::string) const;
    const bool containsSpaceBeforeEquals(std::string);
    const std::string killwhitespaces(std::string);
    const std::string killwst(std::string);
    const std::string getVariableName(std::string, const int);
    std::string getStringBeforeEquals(std::string);
    std::string reverse(std::string);
    const int spaceIndex(std::string) const;
    const int equalsIndex(std::string) const;
    unsigned long calculator(std::string);
};


#endif //PROJECTSDP_INTERPRETATOR_H
