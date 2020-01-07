#ifndef PROJECTSDP_CONTAINER_H
#define PROJECTSDP_CONTAINER_H
#include <map>

class Container {
public:
    void push(std::string, unsigned long);
    const int getNumOfElements() const;
    void print();
    const bool contains(std::string);
    unsigned long& find(std::string);
private:
    std::map<std::string, unsigned long> box;
};


#endif //PROJECTSDP_CONTAINER_H
