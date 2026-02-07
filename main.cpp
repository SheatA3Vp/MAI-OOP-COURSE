#include "./include/Hex.hpp"

int main() {
    Hex a("FFFF");
    Hex b("1");
    Hex c = a.add(b);

    c.print(std::cout);
    std::cout << std::endl;

    std::cout << "Hex the world!" << std::endl;

    return 0;
}