#ifndef PROJECTSDP_FUNCTIONCONTAINER_H
#define PROJECTSDP_FUNCTIONCONTAINER_H
#include <string>
#include <map>

struct FunctionPair{
    std::string funcName;
    std::string funcNameBeforeBrackets;
    std::string expression;
    FunctionPair();
    FunctionPair(std::string funcName, std::string expression, std::string funcNameBeforeBrackets)
    :funcName(funcName), expression(expression), funcNameBeforeBrackets(funcNameBeforeBrackets)
    {}
};

class FunctionContainer {
public:
    void push(std::string, FunctionPair);
    const int getNumOfElements() const;
    void print();
    const std::string getFuncNameBeforeBrackets(std::string);
    const std::string getVarName(std::string);
    const std::string getFuncName(std::string);
    const std::string getExpression(std::string);
    const std::string getVarNameByNameBB(std::string);
    FunctionPair& find(std::string);
    FunctionPair& findByLS(std::string);
    const bool containsVariable(std::string);
    const bool containsFuncName(std::string);
    const bool containsVarNameBeforeBrackets(std::string);
private:
    std::map<std::string, FunctionPair> box;
};


#endif //PROJECTSDP_FUNCTIONCONTAINER_H
