#include "../Matrix.h"
#include <iostream>

int main() {
    Matrix A (12, 6, 73);
    std::cin >> A;
    Matrix A_block =  A.GetBlock(1, 3, PART_HORIZONTAL) * IntModuloP(73, 2);
    std::cout << A_block;
}
