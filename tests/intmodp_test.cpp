#include "../IntModuloP.h"
#include <iostream>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
int main() {
    int p = 7;
    IntModuloP x(17, 2), y (17, 9);
    std::cout << x * (y ^ 2) << std::endl;
    return 0;
}
#pragma clang diagnostic pop