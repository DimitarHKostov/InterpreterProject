#include <iostream>
#include "Container.h"

const int Container::getNumOfElements() const{
    return this->box.size();
}

void Container::push(std::string key, unsigned long value) {
    if(this->contains(key)){
        std::map<std::string, unsigned long>::iterator itr;
        itr = box.begin();
        while(itr->first!=key){
            ++itr;
        }
        itr->second = value;
    }else{
        box.insert(std::pair<std::string, unsigned long>(key, value));
    }
}

const bool Container::contains(std::string current){
    std::map<std::string, unsigned long>::iterator itr;
    for (itr = box.begin(); itr != box.end(); ++itr) {
        if(current==itr->first){
            return true;
        }
    }
    return false;
}

void Container::print(){
    std::map<std::string, unsigned long>::iterator itr;

    for (itr = box.begin(); itr != box.end(); ++itr) {
        std::cout << itr->first << " " << itr->second << std::endl;
    }
}

unsigned long& Container::find(std::string current) {
    std::map<std::string, unsigned long>::iterator itr;

    for (itr = box.begin(); itr != box.end(); ++itr) {
        if(current==itr->first){
            return itr->second;
        }
    }
}
