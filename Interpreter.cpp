#include "Interpreter.h"
#include <iostream>
#include <fstream>
#include <sstream>

Interpreter::Interpreter() {

}

void Interpreter::interpret(std::string fileName) {
    this->toInterpret(fileName);

    for (int i = 0; i < text.getSize(); ++i){
        this->killwhitespaces(text[i]);
        if(isPrint(text[i])){
            this->printManipulator(text[i], i);
        }else if(isRead(text[i])){
            this->readHelper(std::cin, text[i], i);
        }else{
            this->treeManipulator(text[i], i);
        }
    }

    this->errors.printTypeErrors();
    this->errors.printVariableErrors();
    this->errors.printSyntaxErrors();
}

Interpreter::~Interpreter() {

}

void Interpreter::toInterpret(std::string fileName) {
    text.fill(fileName);
}

const bool Interpreter::isPrint(Line& a) const{
    return a.getSavedLine().substr(0,5).compare("print")==0;
}

const bool Interpreter::isRead(Line& a) const{
    return a.getSavedLine().substr(0,4).compare("read")==0;
}

Line& Interpreter::killwhitespaces(Line& a) {
    for(int i = 0; i < a.getSavedLine().length(); ++i){
        std::stringstream ss(a.getSavedLine());
        if(ss.peek()==' '){
            a.getSavedLine().erase(0,1);
        }
    }
    return a;
}

Line& Interpreter::printVariable(Line& a) {
    a.getSavedLine().erase(0,5);
    return this->killwhitespaces(a);
}

Line& Interpreter::readVariable(Line& a) {
    a.getSavedLine().erase(0,4);
    return this->killwhitespaces(a);
}

void Interpreter::printHelper(Line& a, const int currentLine) {
    std::string printLine = this->printVariable(a).getSavedLine();
    if(isFunType(printLine) || isVarType(printLine)){
        if(this->box.contains(printLine)) {
            std::cout << box.find(printLine) << std::endl;
        }else{
            errors.addVariableErrorAtLine(printLine, currentLine);
        }
    }else{
        errors.addTypeErrorAtLine(printLine, currentLine);
    }
}

void Interpreter::readHelper(std::istream& in, Line& a, const int currentLine) {
    Line b = readVariable(a);
    if(isFunType(b.getSavedLine()) || isVarType(b.getSavedLine())){
        unsigned long n;
        in >> n;
        box.push(b.getSavedLine(), n);
    }else{
        errors.addTypeErrorAtLine(b.getSavedLine(), currentLine);
    }
}

const std::string Interpreter::variableSetterHelper(Line& a, const int currentLine) {
    int num = this->numOfEquals(a);
    if(num==1){
        std::string b = killwhitespaces(a).getSavedLine();
        std::string variable = this->getVariableName(b, currentLine);
        return variable;
    }else{
        this->errors.addSyntaxErrorAtLine(currentLine);
    }
}

const bool Interpreter::isVarType(std::string s) const{
    for(int i = 0; i < s.length(); ++i){
        if(s[i]<'a' || s[i]>'z'){
            return false;
        }
    }
    return true;
}

const bool Interpreter::isFunType(std::string s) const{
    for(int i = 0; i < s.length(); ++i){
        if(s[i]<'A' || s[i]>'Z'){
            return false;
        }
    }
    return true;
}

const int Interpreter::spaceIndex(std::string s) const{
    for(int i = 0; i < s.length(); ++i){
        if(s[i]==' '){
            return i;
        }
    }
    return 0;
}

const bool Interpreter::containsEquals(Line& a) const{
    std::string b = a.getSavedLine();
    for(int i = 0; i < b.length(); ++i){
        if(b[i]=='='){
            return true;
        }
    }
    return false;
}

const bool Interpreter::containsSpaceBeforeEquals(std::string b) {
    int i = 0;
    while(b[i]!='='){
        if(b[i]==' '){
            return true;
        }
        ++i;
    }
    return false;
}

const int Interpreter::equalsIndex(std::string s) const {
    for(int i = 0; i < s.length(); ++i){
        if(s[i]=='='){
            return i;
        }
    }
    return 0;
}

const std::string Interpreter::getVariableName(std::string b, const int currentLine) {
    std::string subB = b.substr(0, equalsIndex(b));
    std::string revSubB = this->reverse(subB);
    std::string newSubB = this->killwhitespaces(revSubB);

    if(isVarType(newSubB) || isFunType(newSubB)){
        return this->reverse(newSubB);
    }else{
        this->errors.addTypeErrorAtLine(newSubB, currentLine);
        return "";
    }
}

const std::string Interpreter::buildTreeFrom(Line& a) {
    std::string expr = a.getSavedLine();
    std::string subExpr = expr.substr(this->equalsIndex(expr)+1, expr.length());
    return this->killwst(subExpr);
}

const std::string Interpreter::killwhitespaces(std::string s) {
    for(int i = 0; i < s.length();++i){
        std::stringstream ss(s);
        if(ss.peek()==' '){
            s.erase(0,1);
        }
    }
    return s;
}

const bool Interpreter::containsMoreThanOneEquals(Line& a) const{
    bool flag = false;
    int count = 0;
    for(int i = 0; i < a.getSavedLine().length(); ++i){
        if(a.getSavedLine()[i]=='='){
            count++;
        }
    }
    if(count>1){
        return true;
    }
    return false;
}

const std::string Interpreter::killwst(std::string s) {
    int track = 0;
    for(int i = 0; i < s.length(); ++i){
        if(s[i]==' '){
            s = s.substr(track, i) + s.substr(i+1, s.length());
        }

    }
    return s;
}

const int Interpreter::numOfEquals(Line& a){
    std::string s = a.getSavedLine();
    int count = 0;
    for(int i = 0; i < s.length(); i++){
        if(s[i]=='='){
            count++;
        }
    }
    return count;
}

const Line& Interpreter::killwst(Line& a) {
    std::string s = a.getSavedLine();
    int track = 0;
    for(int i = 0; i<s.length();++i){
        if(s[i]==' '){
            s = s.substr(track, i) + s.substr(i+1, s.length());
        }
    }
    return a;
}

std::string Interpreter::getStringBeforeEquals(std::string s) {
    int i = 0;
    while(s[i]!='='){
        i++;
    }
    s.erase(i, s.length()-1);
    return s;
}

std::string Interpreter::reverse(std::string s) {
    int back = s.length()-1;
    for(int i = 0; i < s.length()/2; i++){
        std::swap(s[i], s[back]);
        back--;
    }
    return s;
}

const bool Interpreter::containsBrackets(Line &a) const{
    std::string checker = a.getSavedLine();
    for(int i = 0; i < checker.length(); ++i){
        if(checker[i]=='[' || checker[i]==']'){
            return true;
        }
    }
    return false;
}

void Interpreter::setVariableAndValue(Line &a, const int currentLine) {
    std::string variableName = this->variableSetterHelper(a, currentLine);
    std::string treeExpression = this->buildTreeFrom(a);
    if(this->containsLetters(treeExpression)){
        std::string treeExpressionAfterConvertion = this->treeExpressionConverter(treeExpression);
        if(this->containsLetters(treeExpressionAfterConvertion)){
            //error, var not found
            //std::cout << "letters" << std::endl;
        }else{
            unsigned long value = this->calculator(treeExpressionAfterConvertion);
            this->box.push(variableName, value);
        }
    }else{
        unsigned long value = this->calculator(treeExpression);
        this->box.push(variableName, value);
    }
}

unsigned long Interpreter::calculator(std::string expression) {
    this->tree.setExpression(expression);
    tree.buildTypeOne();
    return tree.calculate();
}

void Interpreter::printManipulator(Line &s, const int currentLine) {
    if(this->containsBrackets(s)){
        this->printBracketsHelper(s, currentLine);
    }else{
        this->printHelper(s, currentLine);
    }
}

void Interpreter::treeManipulator(Line &s, const int currentLine) {
    if(this->containsBrackets(s)){
        this->bracketTreeExpression(s);
    }else{
        this->setVariableAndValue(s, currentLine);
    }
}

std::string Interpreter::treeExpressionConverter(std::string s) {
    std::string newExpression = "";
    int i = 0;
    int j = 0;
    int varLen = 0;
    while(i < s.length() && s[i]!='/0'){
        if(s[i]>='a' && s[i]<='z'){
            j = i;
            while(s[j]>='a' && s[j]<='z' && j < s.length()){
                newExpression = newExpression + s[j];
                ++j;
                ++varLen;
            }
            if(this->box.contains(newExpression)){
                unsigned long value = this->box.find(newExpression);
                std::stringstream ss;
                ss << value;
                std::string glue = ss.str();
                s = s.substr(0,i) + glue + s.substr(i+varLen, s.length());
                i = 0;
                varLen = 0;
                newExpression = "";
            }else{
                newExpression = "";
            }
        }
        ++i;
    }

    return s;
}

const bool Interpreter::containsLetters(std::string s) {
    for(int i = 0; i < s.length(); ++i){
        if(s[i]>='a' && s[i]<='z'){
            return true;
        }
    }
    return false;
}

void Interpreter::bracketTreeExpression(Line& s) {
    std::string varName = this->getBracketCaseVarName(s);
    std::string funcName = this->getBracketCaseFunctionName(s);
    std::string expression = this->getBracketCaseExpression(s);
    std::string strBB = this->sbb(varName);
    //std::cout << "var name: " << varName << ", func name: " << funcName << ", expr: " << expression << std::endl;
    this->funcBox.push(varName, FunctionPair{funcName, expression,strBB});
}

std::string Interpreter::getBracketCaseVarName(Line &s) {
    std::string lineText = s.getSavedLine();
    std::string varName = "";
    int i = 0;
    while(lineText[i] != '['){
        varName = varName + lineText[i];
        ++i;
    }
    varName = this->killWhiteSpacesFromBehind(varName);
    varName = varName + '[' + this->getBracketCaseFunctionName(s) + ']';
    return varName;
}

std::string Interpreter::getBracketCaseFunctionName(Line &s) {
    std::string lineText = s.getSavedLine();
    std::string varName = "";
    int openBracketIndex = 0;
    int closeBracketIndex = 0;
    while(lineText[openBracketIndex] != '['){
        ++openBracketIndex;
    }
    while(lineText[closeBracketIndex]!=']'){
        ++closeBracketIndex;
    }

    if(openBracketIndex>closeBracketIndex) {
        //da dobavq error
        std::cout << "error" << std::endl;
        return "";
    }
    int start = openBracketIndex + 1;

    varName = lineText.substr(start, closeBracketIndex - start);

    if(varName==""){
        //da dobavq error
        std::cout << "no func name" << std::endl;
        return "";
    }

    varName = this->killwhitespaces(varName);
    varName = this->killWhiteSpacesFromBehind(varName);


    if(this->containsSpace(varName)){
        std::cout << "invalid func name" << std::endl;
        //da dobavq error
        return "";
    }

    return varName;
}

const bool Interpreter::containsSpace(std::string s) const {
    for(int i = 0; i < s.length(); ++i){
        if(s[i] == ' '){
            return true;
        }
    }
    return false;
}

const std::string Interpreter::killWhiteSpacesFromBehind(std::string s) {
    std::string rev = reverse(s);
    for(int i = 0; i < s.length(); ++i){
        std::stringstream ss(rev);
        if(ss.peek()==' '){
            rev.erase(0,1);
        }
    }
    std::string revRev = reverse(rev);
    return revRev;
}

std::string Interpreter::getBracketCaseExpression(Line &s) {
    std::string expr = s.getSavedLine();
    if(this->numOfEquals(s)!=1){
        //error
        return "";
    }else{
        int i = 0;
        while(expr[i]!='='){
            ++i;
        }
        int start = i + 1;
        std::string subExpr = expr.substr(start, expr.length()-start);
        return this->killwst(subExpr);
    }
}

void Interpreter::printBracketsHelper(Line &a, const int currentLine) {
    std::string s = this->killwhitespaces(a.getSavedLine());
    std::string varToBePrinted = this->killWhiteSpacesFromBehind(this->killwhitespaces(s.erase(0,5)));
    std::string varBeforeBrackets = this->sbb(varToBePrinted);
    std::string funcName = this->getBracketCaseFunctionName(a);
    if(this->funcBox.containsVarNameBeforeBrackets(varBeforeBrackets)){
        std::string expr = this->funcBox.findByLS(varBeforeBrackets).expression;
        std::string varName =  funcBox.getVarNameByNameBB(varBeforeBrackets);
        std::string funcNameInsideBox = funcBox.getFuncName(varName);
        std::string realExpr = this->replace(expr, funcNameInsideBox, funcName);
        if(this->box.contains(funcName)){
            std::string str = this->insideHelper(realExpr);
            unsigned long value = this->calculator(str);
            std::cout << value << std::endl;
        }
        else{
            std::cout << "no" << std::endl;
        }
    }else{

    }
}

std::string Interpreter::UnsignedLongToString(unsigned long &x) {
    std::stringstream ss;
    ss << x;
    std::string toString = ss.str();
    return toString;
}

std::string Interpreter::bracketTreeExpressionConverter(std::string s) {
    std::string newExpression = "";
    int i = 0;
    int j = 0;
    //int varLen = 0;
    while(i < s.length() && s[i]!='/0'){
        if(s[i]>='a' && s[i]<='z'){
            j = i;
            while(s[j]>='a' && s[j]<='z' && j < s.length()){
                newExpression = newExpression + s[j];
                ++j;
                //++varLen;
            }
            if(this->funcBox.containsFuncName(newExpression)){
                unsigned long value = this->box.find(newExpression);
                std::stringstream ss;
                ss << value;
                std::string glue = ss.str();
                s = s.substr(0,i) + glue + s.substr(i+1, s.length());
                i = 0;
                newExpression = "";
                //varLen = 0;
            }else{
                newExpression = "";
            }
        }
        ++i;
    }

    return s;
}

std::string Interpreter::insideHelper(std::string s) {
    std::string stringAfterConvertion = this->bracketTreeExpressionConverter(s);
    std::string finalRev = this->treeExpressionConverter(stringAfterConvertion);
    return finalRev;
}

std::string Interpreter::sbb(std::string s) {
    std::string stringBeforeBrackets = "";
    int i = 0;
    while(s[i]!='['){
        stringBeforeBrackets = stringBeforeBrackets + s[i];
        ++i;
    }
    return stringBeforeBrackets;
}

std::string Interpreter::replace(std::string original, std::string oldString, std::string newString) {
    int i = 0;
    int varLen = 0;
    while(i < original.length() && original[i]!='/0'){
        if(original[i]==oldString[0]){
            int start = i+1;
            original = original.substr(0, i) + newString + original.substr(start, original.length()-start);
        }
        ++i;
    }
    return original;
}


