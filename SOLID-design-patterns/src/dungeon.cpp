#include "dungeon.hpp"
#include "npc.hpp"
#include "factory.hpp"
#include "battle_visitor.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_set>

void Dungeon::addNPC(std::unique_ptr<NPC> npc) {
    npcs_.push_back(std::move(npc));
}

void Dungeon::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    for (const auto& npc : npcs_) {
        file << npc->getType() << " " << npc->getName() << " " << npc->getX() << " " << npc->getY() << std::endl;
    }
}

void Dungeon::loadFromFile(const std::string& filename) {
    npcs_ = NPCFactory::loadFromFile(filename);
}

void Dungeon::print() const {
    for (const auto& npc : npcs_) {
        std::cout << npc->getType() << " " << npc->getName() << " at (" << npc->getX() << ", " << npc->getY() << ")" << std::endl;
    }
}

void Dungeon::battle(double range, std::vector<std::shared_ptr<Observer>>& observers) {
    std::unordered_set<std::string> killed;
    for (size_t i = 0; i < npcs_.size(); ++i) {
        if (killed.count(npcs_[i]->getName()) > 0) continue; // Пропускаем уже убитых
        for (size_t j = i + 1; j < npcs_.size(); ++j) {
            if (killed.count(npcs_[j]->getName()) > 0) continue; // Снова пропускаем уже убитых
            if (npcs_[i]->distanceTo(*npcs_[j]) <= range) {
                // A атакует B
                BattleVisitor visitorAB(*npcs_[j], observers, killed);
                npcs_[i]->accept(visitorAB);

                // B атакует A (оба могут умереть в одном раунде)
                BattleVisitor visitorBA(*npcs_[i], observers, killed);
                npcs_[j]->accept(visitorBA);
            }
        }
    }
    // Удаляем убитых
    npcs_.erase(std::remove_if(npcs_.begin(), npcs_.end(),
        [&killed](const std::unique_ptr<NPC>& npc) {
            return killed.count(npc->getName()) > 0;
        }), npcs_.end());
}