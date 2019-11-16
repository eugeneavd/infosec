#include "Matrix.h"
#include "includes.h"
#include <vector>
#include <iostream>
#include <iomanip>

std::ostream& operator<<(std::ostream& out, const Matrix& A) {
   out << std::setfill(' ');
    for (const auto& row: A.mat) {
        for (const auto &elem: row)
            out << std::setw(4) << elem;
        out << "\n";
    }
    return out;
}

std::istream& operator>>(std::istream& in, Matrix& A) {
    /*
     matrix size is determined during creation
    in >> A.m >> A.n;
    A.resize(A.m, A.n);
     */
    for (auto& row: A.mat)
        for (auto& elem: row)
            in >> elem;
    return in;
}

void Matrix::resize(int m, int n) {
    mat = std::vector<std::vector<IntModuloP>>  (m, std::vector<IntModuloP>(n, 0));
    this->m = m;
    this->n = n;
}


Matrix::Matrix(int m, int n) : Matrix() {
    resize(m, n);
}

IntModuloP& Matrix::operator()(int m, int n) {
    return mat[m][n];
}

Matrix Mult(const Matrix &A, const Matrix &B) {
    int m = A.m;
    int l = A.n; // assuming A.n = B.m
    int n = B.n;
    Matrix C(m, n);
    for (int i=0; i < m; i++)
        for (int j=0; j < n; j++)
            for (int k=0; k < l; k++)
                C.mat[i][j] += A.mat[i][k] * B.mat[k][j];
    return C;
}

Matrix::Matrix(int m, int n, int sockfd) : Matrix(m, n){
    int buff[MAX];
    for (int i = 0; i < m; i++) {
        bzero(buff, MAX);
        read(sockfd, buff, sizeof(buff));
        for (int j = 0; j < n; j++) {
            mat[i][j] = IntModuloP(buff[j]);
        }
    }
}

void Matrix::Send(int sockfd) const {
    int buff[MAX];
    for(int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            buff[j] = mat[i][j];
        }
        write(sockfd, buff, sizeof(buff));
    }
}
