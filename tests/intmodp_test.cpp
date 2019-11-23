#include "../IntModuloP.h"
#include <iostream>

int main() {
    int p = 7;
    IntModuloP x(7, 2), y (7, 1);
    std::cout << y / x;
    return 0;
}