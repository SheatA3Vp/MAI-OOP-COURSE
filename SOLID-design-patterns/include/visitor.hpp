#pragma once
#include <vector>
#include <memory>
#include <unordered_set>
#include <string>

class NPC;
class Observer;

class Visitor {
public:
    Visitor(NPC& other, std::vector<std::shared_ptr<Observer>>& observers, std::unordered_set<std::string>& killed);
    virtual ~Visitor() = default;

    virtual void visitBear(class Bear& bear) = 0;
    virtual void visitHeron(class Heron& heron) = 0;
    virtual void visitDesman(class Desman& desman) = 0;

protected:
    NPC& other_;
    std::vector<std::shared_ptr<Observer>>& observers_;
    std::unordered_set<std::string>& killed_;
};