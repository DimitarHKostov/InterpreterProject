#include "errorContainer.h"
#include <iostream>

void errorContainer::addVariableErrorAtLine(std::string key, int value) {
    this->variableErrors.insert(std::pair<std::string, int>(key, value));
}

void errorContainer::printVariableErrors() {
    std::map<std::string, int>::iterator itr;

    for (itr = variableErrors.begin(); itr != variableErrors.end(); ++itr) {
        std::cout << "Error found at Line: " << itr->second+1 <<", variable " << itr->first << " not found!" << std::endl;
    }
}

void errorContainer::addTypeErrorAtLine(std::string key, int value) {
    this->typeErrors.insert(std::pair<std::string, int>(key, value));
}

void errorContainer::printTypeErrors() {
    std::map<std::string, int>::iterator itr;

    for (itr = typeErrors.begin(); itr != typeErrors.end(); ++itr) {
        std::cout << "Error found at Line: " << itr->second+1 <<", type of the variable " << itr->first << " is not Var nor Fun!" << std::endl;
    }
}

void errorContainer::addSyntaxErrorAtLine(int line) {
    this->syntaxErrors.push_back(line);
}

void errorContainer::printSyntaxErrors() {
    for(int i = 0; i < this->syntaxErrors.size(); ++i){
        std::cout << "Syntax error at line: " << this->syntaxErrors[i]+1 << "!" << std::endl;
    }
}


