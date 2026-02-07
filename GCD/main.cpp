#include <iostream>
#include "include/GCD.hpp"


int main() {
    int n;
    int m;
    std::cin >> n >> m;
    std::cout << GCD(n, m) << std::endl;
    return 0;
}