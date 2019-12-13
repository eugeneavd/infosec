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
    const IntModuloP& operator()(int m, int n) const;
    friend Matrix operator*(const Matrix& A, const Matrix& B);
    Matrix operator+(const Matrix& A) const;
    friend std::istream& operator>>(std::istream& in, Matrix& A);
    friend std::ostream& operator<<(std::ostream& out, const Matrix& A);
    friend bool operator==(const Matrix& lhs, const Matrix& rhs);
    friend Matrix IdentityMatrix(int N, int prime);
    void resize(int m, int n);
    void Transpose();
    Matrix operator*(IntModuloP a) const;
    Matrix GetBlock(int block_num, int parts_num, short direction) const;
    void SetBlock(int block_num, int parts_num, short direction, const Matrix& block);
    void SetBlock(int v_num, int h_num, int vert_num, int hor_num, const Matrix& block);
    int GetMod() const;
    std::pair<int, int> GetSize() const;
    void FillRandomly();
    std::pair<bool, Matrix> Inverse() const;
protected:
    std::vector<std::vector<IntModuloP>> mat;
    int m=0, n=0;
    int mod=1;
};

std::ostream& operator<<(std::ostream& out, const Matrix& A);
std::istream& operator>>(std::istream& in, Matrix& A);
bool operator==(const Matrix& lhs, const Matrix& rhs);
Matrix operator*(const Matrix& A, const Matrix& B);

Matrix IdentityMatrix(int N, int prime);
Matrix Vandermonde(const std::vector<IntModuloP>& a, const std::vector<int>& deg);

#endif //INFOSEC_MATRIX_H
