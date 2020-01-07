#include <cstring>
#include "Line.h"
#include <sstream>
#include <iostream>

Line::Line(){
    this->currentLine=1;
}

Line::Line(std::string e){
    this->currentLine=1;
    this->expression=e;
}

bool Line::saveAs(std::string e) {
    this->expression=e;
}

void Line::push(std::string str, int number) {
    this->container.push(str, number);
}

std::string& Line::getSavedLine() {
    return this->expression;
}

const int Line::getCurrentLine() const {
    return this->currentLine;
}

void Line::nextLine() {
    this->currentLine++;
}

Line::~Line() {

}

std::string Line::killWhiteSpaces() {
    std::stringstream ss(this->getSavedLine());
    int counter = 0;
    while(ss.peek()== ' ' || ss.peek()=='\n'){
        ss.get();
        counter++;
    }
    return ss.str();
}
