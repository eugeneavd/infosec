#include "Matrix.h"
#include "DegreeTable.h"
#include<vector>


#ifndef INFOSEC_CODER_H
#define INFOSEC_CODER_H

class Coder
{
private:
    const int K, L, T;
    vector<Matrix> f, g;
    DegreeTable dg;
    const vector<int>& Adegrees;
    const vector<int>& Bdegrees;
    vector<IntModuloP> a;
    int N;
    int mod;
    set<int> terms {};
    Matrix ReverseVdm;
    vector<vector<int>> DegMatr;

public:
    Coder(int K, int L, int T, vector<IntModuloP> &val_a, int seed = 0);
    Coder(int K, int L, int T, int seed = 0);
    void Code(Matrix A, Matrix B);
    const vector<Matrix> &GetF() const;
    const vector<Matrix> &GetG() const;
    const int &GetN() const;
    const Matrix& GetVinv() const;
    vector<int> GetTerms() const;
    const vector<IntModuloP> &GetA() const;
    void SetA(vector<IntModuloP> &val);
    const vector<vector<int>> &GetDegMatr() const;
    void SetARandom();
};

#endif //INFOSEC_CODER_H