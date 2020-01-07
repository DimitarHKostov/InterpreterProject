#include "FunctionContainer.h"
#include <iostream>

void FunctionContainer::push(std::string key, FunctionPair value) {
    box.insert(std::pair<std::string, FunctionPair>(key, value));
}

const int FunctionContainer::getNumOfElements() const {
    return this->box.size();
}

void FunctionContainer::print() {

}

FunctionPair& FunctionContainer::find(std::string current) {
    std::map<std::string, FunctionPair>::iterator itr;

    for (itr = box.begin(); itr != box.end(); ++itr) {
        if(current==itr->first){
            return itr->second;
        }
    }
    FunctionPair a({"","",""});
    return a;
}

const std::string FunctionContainer::getFuncName(std::string current) {
    std::map<std::string, FunctionPair>::iterator itr;

    for (itr = box.begin(); itr != box.end(); ++itr) {
        if(current==itr->first){
            return itr->second.funcName;
        }
    }
    return "";
}

const std::string FunctionContainer::getExpression(std::string current) {
    std::map<std::string, FunctionPair>::iterator itr;

    for (itr = box.begin(); itr != box.end(); ++itr) {
        if(current==itr->first){
            return itr->second.expression;
        }
    }
    return "";
}

const std::string FunctionContainer::getVarName(std::string current) {
    std::map<std::string, FunctionPair>::iterator itr;
    for (itr = box.begin(); itr != box.end(); ++itr) {
        if(current==itr->first){
            return itr->first;
        }
    }
    return "";
}

const bool FunctionContainer::containsVariable(std::string s) {
    std::map<std::string, FunctionPair>::iterator itr;
    for (itr = box.begin(); itr != box.end(); ++itr) {
        if(s==itr->first){
            return true;
        }
    }
    return false;
}

const bool FunctionContainer::containsFuncName(std::string s) {
    std::map<std::string, FunctionPair>::iterator itr;
    for (itr = box.begin(); itr != box.end(); ++itr) {
        if(s==itr->second.funcName){
            return true;
        }
    }
    return false;
}

const bool FunctionContainer::containsVarNameBeforeBrackets(std::string s) {
    std::map<std::string, FunctionPair>::iterator itr;
    for (itr = box.begin(); itr != box.end(); ++itr) {
        if(s==itr->second.funcNameBeforeBrackets){
            return true;
        }
    }
    return false;
}

const std::string FunctionContainer::getFuncNameBeforeBrackets(std::string s) {
    std::map<std::string, FunctionPair>::iterator itr;
    std::string beforeBrackets = "";
    int i = 0;
    while(s[i]!='['){
        beforeBrackets = beforeBrackets + s[i];
        ++i;
    }
    for (itr = box.begin(); itr != box.end(); ++itr) {
        if(beforeBrackets==itr->second.funcNameBeforeBrackets){
            return itr->second.funcNameBeforeBrackets;
        }
    }
    return "";
}

FunctionPair &FunctionContainer::findByLS(std::string s) {
    std::map<std::string, FunctionPair>::iterator itr;
    for (itr = box.begin(); itr != box.end(); ++itr) {
        if(s==itr->second.funcNameBeforeBrackets){
            return itr->second;
        }
    }
    FunctionPair a({"","",""});
    return a;
}

const std::string FunctionContainer::getVarNameByNameBB(std::string s) {
    std::map<std::string, FunctionPair>::iterator itr;
    for (itr = box.begin(); itr != box.end(); ++itr) {
        if(s==itr->second.funcNameBeforeBrackets){
            return itr->first;
        }
    }
    return "";
}
