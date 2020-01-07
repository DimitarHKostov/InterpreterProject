#ifndef PROJECTSDP_EXPRESSIONTREENODE_H
#define PROJECTSDP_EXPRESSIONTREENODE_H
#include <string>


struct expressionTreeNode {
    std::string data;
    expressionTreeNode *left, *right;
    void setData(std::string data){
        this->data=data;
    }

    expressionTreeNode(std::string data = "!", expressionTreeNode *left = nullptr, expressionTreeNode *right = nullptr)
            : data(data), left(left), right(right)
    {}
};


#endif //PROJECTSDP_EXPRESSIONTREENODE_H
