#include "Matrix.h"
#include "includes.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <utility>

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
    mat = std::vector<std::vector<IntModuloP>>  (m, std::vector<IntModuloP>(n, IntModuloP(mod, 0)));
    this->m = m;
    this->n = n;
}


Matrix::Matrix(int m, int n, int mod) : mod(mod) {
    resize(m, n);
}

IntModuloP& Matrix::operator()(int m, int n) {
    return mat[m][n];
}

Matrix operator*(const Matrix &A, const Matrix &B) {
    int m = A.m;
    int l = A.n; // assuming A.n = B.m
    int n = B.n;
    Matrix C(m, n, A.mod); // A.mod == B.mod
    Matrix Bt = B;
    Bt.Transpose();
    for (int i=0; i < m; i++)
        for (int j=0; j < n; j++)
            for (int k=0; k < l; k++)
                C.mat[i][j] = C.mat[i][j] + A.mat[i][k] * Bt.mat[j][k];
    return C;
}

bool operator==(const Matrix &lhs, const Matrix &rhs) {
    if (lhs.GetSize() != rhs.GetSize())
        throw std::invalid_argument ("Can't compare matrices with different dimensions");
    if (lhs.mod != rhs.mod)
        throw std::invalid_argument ("Can't compare matrices over different fields");
    return lhs.mat == rhs.mat;
}

Matrix::Matrix(int m, int n, int mod, int sockfd) : Matrix(m, n, mod){
    int buff[n];
    for (int i = 0; i < m; i++) {
        bzero(buff, m);
        read(sockfd, buff, sizeof(buff));
        for (int j = 0; j < n; j++) {
            mat[i][j] = IntModuloP(mod, buff[j]);
        }
    }
}

void Matrix::Send(int sockfd) const {
    int buff[n];
    for(int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            buff[j] = static_cast<int> (mat[i][j]);
        }
        write(sockfd, buff, sizeof(buff));
    }
}

void Matrix::Transpose() {
    const auto temp = mat;
    resize(n, m);
    for (int i=0; i < m; i++)
        for (int j=0; j < n; j++)
            mat[i][j] = temp[j][i];
}

Matrix Matrix::operator*(IntModuloP a) const {
    Matrix aA(m, n, mod);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            aA(i, j) = a * mat[i][j];
    return aA;
}

Matrix Matrix::GetBlock(int block_num, int parts_num, short direction) const {
    if (direction == PART_HORIZONTAL) {
        // check if (*, n) dimension is appropriate for horizontal partion
        if (n % parts_num) {
            throw std::invalid_argument("Can't partition matrix with size (*, "
                                        + std::to_string(n) + ") into " + std::to_string(parts_num) + " parts.");
        }
        // check block number, it starts from 0
        if (block_num >= parts_num)
            throw std::invalid_argument(" block_num should be less than number of parts");
        int chunk_size = n / parts_num;
        Matrix Block(m, chunk_size, mod);
        for (int i = 0; i < Block.m; i++)
            for (int j = 0; j < Block.n; j++)
                Block.mat[i][j] = mat[i][j + block_num * chunk_size];
        return Block;
    } else if (direction == PART_VERTICAL) {
        // check if (m, *) dimension is appropriate for horizontal partion
        if (m % parts_num) {
            throw std::invalid_argument("Can't partition matrix with size ("
                                        + std::to_string(m) + ", *) into " + std::to_string(parts_num) + " parts.");
        }
        // check block number, it starts from 0
        if (block_num >= parts_num)
            throw std::invalid_argument(" block_num should be less than number of parts");
        const int chunk_size = m / parts_num;
        Matrix Block(chunk_size, n, mod);
        for (int i = 0; i < Block.m; i++)
            for (int j = 0; j < Block.n; j++)
                Block.mat[i][j] = mat[i + block_num * chunk_size][j];
        return Block;
    } else
        throw std::invalid_argument("Direction is either PART_HORIZONTAL or PART_VERTICAL");
}

std::pair<int, int> Matrix::GetSize() const {
    return std::pair<int, int>(m, n);
}

int Matrix::GetMod() const{
    return mod;
}

Matrix Matrix::operator+(const Matrix &A) const {
    const auto [ma, na] = A.GetSize();
    const int q = A.GetMod();
    if ((ma != m) || (na != n))
        throw std::invalid_argument("Matrix sizes are incompatible");
    if (mod != q)
        throw std::invalid_argument("Matrix are over different fields");
    Matrix Sum(ma, na, mod);
    for (int i=0; i < ma; i++)
        for (int j=0; j < na; j++)
            Sum.mat[i][j] = mat[i][j] + A.mat[i][j];
    return Sum;
}

// if you want consistent random matrix generation use predefined srand
void Matrix::FillRandomly() {
    for (auto& row: mat)
        for (auto& elem: row)
            elem = IntModuloP(mod, rand());
}

std::pair<bool, Matrix>
Matrix::Inverse() const {
    if (m != n) throw std::invalid_argument("Matrix is not square");

    const int N = m;
    auto A = mat;
    auto I = IdentityMatrix(N, mod);

    const IntModuloP zero(mod, 0);
    const IntModuloP one(mod, 1);
    IntModuloP coef(mod, 1);
    IntModuloP __inv(mod, 1);
    //perform direct Gauss elimination and apply same to one
    for (int i = 0; i < N; i++) {

/*
        for (const auto& row: A) {
            for (const auto &elem: row)
                std::cout << elem << ' ';
            std::cout << std::endl;
        }
        std::cout << I;
*/

        // choose leading element
        if (A[i][i] == zero) {
            bool found = false;
            for (int j=i + 1; j < N; j++) {
                if ((A[i][j] == zero)) {
                    found = true;
                    for (int k = 0; k < N; k++) {
                        std::swap(A[i][k], A[j][k]);
                        std::swap(I.mat[i][k], I.mat[j][k]);
                    }
                    break;
                }
            }
            if (! found)
                return std::make_pair(false, Matrix());
        }
        __inv = one / A[i][i];
        for (int j = i + 1; j < N; j++) {
            coef = __inv * A[j][i];
            for (int k = 0; k < N; k++) {
                A[j][k] = A[j][k] - A[i][k] * coef;
                I.mat[j][k] = I.mat[j][k] - I.mat[i][k] * coef;
            }
        }
        for (int k=0; k < N; k++) {
            A[i][k] = A[i][k] * __inv;
            I.mat[i][k] = I.mat[i][k] * __inv;
        }
    }

    // perform reverse Gauss elimination
    // matrix has only 1s one diagonal

    for (int i = N - 1; i >= 0; i--) {
/*
        for (const auto& row: A) {
            for (const auto &elem: row)
                std::cout << elem << ' ';
            std::cout << std::endl;
        }
        std::cout << I;
*/
        for (int j = i - 1; j >= 0; j--)
            for (int k = 0; k < N; k++) {
                I.mat[j][k] = I.mat[j][k] - I.mat[i][k] * A[j][i];
                A[j][k] = A[j][k] - A[i][k] * A[j][i];
            }
    }
    return std::make_pair(true, I);
}

Matrix IdentityMatrix(int N, int prime) {
    Matrix I(N, N, prime);
    for (int i = 0; i < N; i++)
        I.mat[i][i] = IntModuloP(prime, 1);
    return I;
}

void Matrix::SetElem(int row, int col, IntModuloP x) {
    if (x.GetMod() != mod)
        throw std::invalid_argument("Can't set matrix elem to x of different field");
    if (!((0 <= row) && (row < m)) || !((0 <= col) && (col < n)))
        throw std::invalid_argument("Can't set matrix elem to x, out of range");
    mat[row][col] = x;
}


