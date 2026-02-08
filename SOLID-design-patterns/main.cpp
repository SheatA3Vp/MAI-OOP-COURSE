#include "dungeon.hpp"
#include "factory.hpp"
#include "console_observer.hpp"
#include "file_observer.hpp"
#include <iostream>
#include <memory>
#include <fstream>
#include <random>

int main(int argc, char* argv[]) {
    Dungeon dungeon;
    auto consoleObs = std::make_shared<ConsoleObserver>();
    auto fileObs = std::make_shared<FileObserver>("log.txt");
    std::vector<std::shared_ptr<Observer>> observers = {consoleObs, fileObs};

    std::cout << "=== Dungeon Editor ===" << std::endl << std::endl;

    const bool loadFromFile = argc > 1;
    std::string npcFile = "npcs.txt";

    if (loadFromFile) {
        npcFile = argv[1];
        std::cout << "Loading NPCs from file '" << npcFile << "'..." << std::endl;
        dungeon.loadFromFile(npcFile);
    } else {
        std::cout << "Generating NPCs with random coordinates..." << std::endl;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(0.0, 500.0);

        dungeon.addNPC(NPCFactory::createNPC("Bear", "Bear1", dist(gen), dist(gen)));
        dungeon.addNPC(NPCFactory::createNPC("Heron", "Heron1", dist(gen), dist(gen)));
        dungeon.addNPC(NPCFactory::createNPC("Desman", "Desman1", dist(gen), dist(gen)));
        dungeon.addNPC(NPCFactory::createNPC("Bear", "Bear2", dist(gen), dist(gen)));

        std::cout << "\nSaving NPCs to file '" << npcFile << "'..." << std::endl;
        dungeon.saveToFile(npcFile);
    }

    std::cout << "Initial NPCs in the dungeon:" << std::endl;
    dungeon.print();

    // Битва
    std::cout << "\n=== Starting Battle ===" << std::endl;
    std::cout << "Battle range: 50 meters" << std::endl;
    std::cout << "Battle log:" << std::endl;
    dungeon.battle(50.0, observers);

    std::cout << "\n=== Battle Results ===" << std::endl;
    std::cout << "Remaining NPCs after battle:" << std::endl;
    dungeon.print();

    std::cout << "\n=== Loading NPCs from file ===" << std::endl;
    Dungeon dungeon2;
    dungeon2.loadFromFile(npcFile);
    std::cout << "Loaded NPCs:" << std::endl;
    dungeon2.print();

    std::cout << "\n=== Battle events logged to 'log.txt' ===" << std::endl;
    std::cout << "\nProgram finished successfully!" << std::endl;

    return 0;
}
