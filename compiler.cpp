#include <iostream>
#include "Line.h"
#include "textContainer.h"
#include "Container.h"
#include "FunctionContainer.h"
#include "errorContainer.h"
#include "expressionTreeNode.h"
#include "expressionTree.h"
#include "Interpreter.h"


int main() {

    Interpreter first;
    first.interpret("interpreter.txt");

    //FunctionContainer a;
    //a.push("d[x]", FunctionPair({"x", "a + b + x", "d"}));
    //std::cout << a.getExpression("d[x]") << std::endl;
    //std::cout << a.getFuncName("d[x]") << std::endl;
    //std::cout << a.getFuncNameBeforeBrackets("d[x]") << std::endl;



    return 0;
}