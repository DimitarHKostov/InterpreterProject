#ifndef PROJECTSDP_LINE_H
#define PROJECTSDP_LINE_H
#include <string>
#include "Container.h"

class Line {
public:
    Line();
    ~Line();
    Line(std::string);

    virtual bool saveAs(std::string);
    virtual void push(std::string, int);
    virtual std::string& getSavedLine();
    virtual const int getCurrentLine() const;
    virtual void nextLine();
    virtual std::string killWhiteSpaces();
protected:
    int currentLine;
    Container container;
    std::string expression;
    std::string lineType;
};


#endif //PROJECTSDP_LINE_H
