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
    vector<int> terms {};
    Matrix ReverseVdm;
    vector<vector<int>> DegMatr;
public:
    const Matrix &GetReverseVdm() const;

    const vector<vector<int>> &GetDegMatr() const;

public:
    Coder(int K, int L, int T, vector<IntModuloP> &val_a, int prime, int seed = 0);
    Coder(int K, int L, int T, int prime, int seed = 0);
    void Code(Matrix A, Matrix B);
    const vector<Matrix> &GetF() const;
    const vector<Matrix> &GetG() const;
    const int &GetN() const;
    const vector<int> &GetTerms() const;
    const vector<IntModuloP> &GetA() const;
    void SetA(vector<IntModuloP> &val);
    void SetMod(int prime);
    void SetARandom(int seed = 0);
};

#endif //INFOSEC_CODER_H