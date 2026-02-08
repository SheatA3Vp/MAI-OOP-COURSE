#include "battle_visitor.hpp"
#include "bear.hpp"
#include "heron.hpp"
#include "desman.hpp"
#include "observer.hpp"

BattleVisitor::BattleVisitor(NPC& other, std::vector<std::shared_ptr<Observer>>& observers, std::unordered_set<std::string>& killed)
    : Visitor(other, observers, killed) {}

void BattleVisitor::visitBear(Bear& bear) {
    // Медведь ест всех кроме медведей
    if (other_.getType() != "Bear") {
        for (auto& obs : observers_) {
            obs->onKill(bear.getName(), other_.getName());
        }
        killed_.insert(other_.getName());
    }
}

void BattleVisitor::visitHeron(Heron& heron) {
    // Выпь никого не обижает
}

void BattleVisitor::visitDesman(Desman& desman) {
    // Выхухоль убивает медведей
    if (other_.getType() == "Bear") {
        for (auto& obs : observers_) {
            obs->onKill(desman.getName(), other_.getName());
        }
        killed_.insert(other_.getName());
    }
}