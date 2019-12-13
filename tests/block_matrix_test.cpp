#include "../Matrix.h"
#include <iostream>
#include <cstdlib>

int main() {
    Matrix A(2, 2, 73);
    A(0, 0) = IntModuloP(73, 1);
    A(0, 1) = IntModuloP(73, 2);
    A(1, 0) = IntModuloP(73, 3);
    A(1, 1) = IntModuloP(73, 4);
    Matrix v1(2, 1, 73), v2 (2, 1, 73);
    v1(0, 0) = IntModuloP(73, 7);
    v1(1, 0) = IntModuloP(73, 8);
    v2(0, 0) = IntModuloP(73, 9);
    v2(1, 0) = IntModuloP(73, 10);
    Matrix h1(1, 2, 73), h2 (1, 2, 73);
    h1(0, 0) = IntModuloP(73, 11);
    h1(0, 1) = IntModuloP(73, 12);
    h2(0, 0) = IntModuloP(73, 13);
    h2(0, 1) = IntModuloP(73, 14);
    std::cout << "===== GetBlock =====" << std::endl;
    std::cout << "Сама матрица:" << std::endl;
    std::cout << A << std::endl;
    std::cout << "Первый столбец:" << std::endl;
    std::cout << A.GetBlock(0, 2, PART_HORIZONTAL);
    std::cout << "Второй столбец:" << std::endl;
    std::cout << A.GetBlock(1, 2, PART_HORIZONTAL);
    std::cout << "Первая строка:" << std::endl;
    std::cout << A.GetBlock(0, 2, PART_VERTICAL);
    std::cout << "Вторая строка:" << std::endl;
    std::cout << A.GetBlock(1, 2, PART_VERTICAL);
    std::cout << "===== [av1, v1]=====" << std::endl;
    try {
        A.SetBlock(1, 2, PART_HORIZONTAL, v1);
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    std::cout << A << std::endl;
    std::cout << "===== [av1, v2]=====" << std::endl;
    try {
        A.SetBlock(1, 2, PART_HORIZONTAL, v2);
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    std::cout << A << std::endl;
    std::cout << "===== [v1, v2]=====" << std::endl;
    try {
        A.SetBlock(0, 2, PART_HORIZONTAL, v1);
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    std::cout << A << std::endl;
    std::cout << "=====[v11 v21 ]=====" << std::endl;
    std::cout << "     [ h2     ]     " << std::endl;
    try {
        A.SetBlock(1, 2, PART_VERTICAL, h2);
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    std::cout << A << std::endl;
    std::cout << "=====[ h1     ]=====" << std::endl;
    std::cout << "     [ h2     ]     " << std::endl;
    try {
        A.SetBlock(0, 2, PART_VERTICAL, h1);
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
    std::cout << A << std::endl;
    return 0;
}
