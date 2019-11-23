#include "IntModuloP.h"
#include <iostream>
#include <vector>
#include <iostream>
#ifndef INFOSEC_MATRIX_H
#define INFOSEC_MATRIX_H


class Matrix {
public:
    Matrix() = default;
    Matrix(int m, int n, int prime);
    Matrix(int m, int n, int prime, int sockfd);
    void Send(int sockfd) const;
    IntModuloP& operator()(int m, int n);
    friend Matrix Mult(const Matrix& A, const Matrix& B);
    friend std::istream& operator>>(std::istream& in, Matrix& A);
    friend std::ostream& operator<<(std::ostream& out, const Matrix& A);
    void resize(int m, int n);
    void Transpose();
    Matrix operator*(const IntModuloP a) const;
private:
    std::vector<std::vector<IntModuloP>> mat;
    int m=0, n=0;
    int mod;
};

std::ostream& operator<<(std::ostream& out, const Matrix& A);
std::istream& operator>>(std::istream& in, Matrix& A);

#endif //INFOSEC_MATRIX_H
