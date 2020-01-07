#ifndef PROJECTSDP_ERRORCONTAINER_H
#define PROJECTSDP_ERRORCONTAINER_H

#include <vector>
#include <string>
#include <map>

class errorContainer {
public:
    void addVariableErrorAtLine(std::string, int);
    void addTypeErrorAtLine(std::string, int);
    void addSyntaxErrorAtLine(int);
    void printVariableErrors();
    void printSyntaxErrors();
    void printTypeErrors();
private:
    std::map<std::string, int> variableErrors;
    std::map<std::string, int> typeErrors;
    std::vector<int> syntaxErrors;
};


#endif //PROJECTSDP_ERRORCONTAINER_H
