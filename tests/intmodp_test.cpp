#include "../IntModuloP.h"
#include <iostream>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
int main() {
    int p = 7;
    IntModuloP x(17, 8), y (17, 1);
    std::cout << (x^3) << std::endl;
    return 0;
}
#pragma clang diagnostic pop