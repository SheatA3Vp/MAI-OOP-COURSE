#pragma once
#include <vector>
#include <memory>
#include <string>
#include "npc.hpp"
#include "observer.hpp"

class Dungeon {
public:
    void addNPC(std::unique_ptr<NPC> npc);
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    void print() const;
    void battle(double range, std::vector<std::shared_ptr<Observer>>& observers);

private:
    std::vector<std::unique_ptr<NPC>> npcs_;
};