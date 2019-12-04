#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-nodiscard"
#include "IntModuloP.h"
#include <iostream>
#include <vector>
#include <iostream>
#include <utility>
#ifndef INFOSEC_MATRIX_H
#define INFOSEC_MATRIX_H

#define PART_HORIZONTAL 0
#define PART_VERTICAL   1

class Matrix {
public:
    Matrix() = default;
    Matrix(int m, int n, int prime);
    Matrix(int m, int n, int prime, int sockfd);
    void Send(int sockfd) const;
    IntModuloP& operator()(int m, int n);
    friend Matrix Mult(const Matrix& A, const Matrix& B);
    Matrix operator+(const Matrix& A) const;
    friend std::istream& operator>>(std::istream& in, Matrix& A);
    friend std::ostream& operator<<(std::ostream& out, const Matrix& A);
    friend bool operator==(const Matrix& lhs, const Matrix& rhs);
    void resize(int m, int n);
    void Transpose();
    Matrix operator*(IntModuloP a) const;
    Matrix GetBlock(int block_num, int parts_num, short direction) const;
    int GetMod() const;
    std::pair<int, int> GetSize() const;
    void FillRandomly();
private:
    std::vector<std::vector<IntModuloP>> mat;
    int m=0, n=0;
    int mod=1;
};

std::ostream& operator<<(std::ostream& out, const Matrix& A);
std::istream& operator>>(std::istream& in, Matrix& A);
bool operator==(const Matrix& lhs, const Matrix& rhs);

#endif //INFOSEC_MATRIX_H

#pragma clang diagnostic pop