#include "../Matrix.h"
#include <iostream>
#include <cstdlib>

int main() {
    std::vector<IntModuloP> a (2);
    a[0] = IntModuloP(73, 1);
    a[1] = IntModuloP(73, 3);
    auto deg = {0, 2};
    std::cout << Vandermonde(a, deg);
    return 0;
}
