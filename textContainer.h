#ifndef PROJECTSDP_TEXTCONTAINER_H
#define PROJECTSDP_TEXTCONTAINER_H
#include "Line.h"
#include <vector>
#include <fstream>
#include <iostream>

class textContainer {
public:
    void fill(std::string);
    const int getSize() const;
    std::vector<Line> getText() const;
    Line& operator[](int);
private:
    std::vector<Line> lines;
};


#endif //PROJECTSDP_TEXTCONTAINER_H
