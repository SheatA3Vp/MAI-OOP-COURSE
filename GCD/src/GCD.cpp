#include <algorithm>

int GCD(int a, int b) {
    int temp;
    if (a == 0 && b == 0) return -1; // GCD не определён для (0, 0)
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return std::abs(a);
}
