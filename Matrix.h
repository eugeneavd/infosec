#include "IntModuloP.h"
#include <vector>
#ifndef INFOSEC_MATRIX_H
#define INFOSEC_MATRIX_H


class Matrix {
public:
    Matrix() = default;
    Matrix(int m, int n);
    Matrix(int m, int n, int sockfd);
    void Send(int sockfd) const;
    IntModuloP& operator()(int m, int n);
    friend Matrix Mult(const Matrix& A, const Matrix& B);
    friend std::istream& operator>>(std::istream& in, Matrix& A);
    friend std::ostream& operator<<(std::ostream& out, const Matrix& A);
    void resize(int m, int n);
private:
    std::vector<std::vector<IntModuloP>> mat;
    int m=0, n=0;
};

std::ostream& operator<<(std::ostream& out, const Matrix& A);
std::istream& operator>>(std::istream& in, Matrix& A);

#endif //INFOSEC_MATRIX_H
