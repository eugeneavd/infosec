#include "../Matrix.h"
#include <iostream>
#include <cstdlib>

int main() {
    Matrix A (12, 6, 73);
    Matrix B (12, 6, 73);
    srand(0);
    A.FillRandomly();
    B.FillRandomly();
    std::cout << A;
    std::cout << B;
    std::cout << (A == B);
    return 0;
}
