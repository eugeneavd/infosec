#include "../IntModuloP.h"
#include "../Matrix.h"
#include <iostream>
#include <fstream>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"
int main() {
    Matrix V(8, 8, 73);
    std::ifstream f;
    f.open("mat.txt");
    f >> V;
    std::cout << V;
    const auto [IsInv, Vinv] = V.Inverse();
    std::cout << IsInv;
    std::cout << V*Vinv;
    return 0;
}
#pragma clang diagnostic pop