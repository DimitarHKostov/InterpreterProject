#include <cstring>
#include "textContainer.h"

void textContainer::fill(std::string fileName) {
    std::string line;
    std::ifstream file;

    file.open(fileName);
    while (getline(file, line)){
        this->lines.push_back(line);
    }

    file.close();
}

const int textContainer::getSize() const {
    return this->lines.size();
}

std::vector<Line> textContainer::getText() const {
    return this->lines;
}

Line& textContainer::operator[](int index) {
    return this->lines[index];
}

