#include "../Matrix.h"
#include <iostream>
#include <cstdlib>

int main() {
    auto A = Matrix(2,2,7);
    A.SetElem(0, 0, IntModuloP(7, 1));
    A.SetElem(0, 1, IntModuloP(7, 2));
    A.SetElem(1, 0, IntModuloP(7, 3));
    A.SetElem(1, 1, IntModuloP(7, 4));
    auto [_, A_inv] = A.Inverse();
    auto [__, A_inv_inv] = A_inv.Inverse();
    std::cout << A_inv_inv << std::endl;
    std::cout << A << std::endl;
    auto [isInv, B] = A.Inverse();
    return 0;
}
