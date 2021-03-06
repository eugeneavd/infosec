#include "Coder.h"
#include "includes.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <cassert>


Coder::Coder(int K, int L, int T, vector<IntModuloP> &val_a, int prime, int seed) : K(K), L(L), T(T), dg(DegreeTable(K, L, T)), Adegrees(dg.GetAlpha()), Bdegrees(dg.GetBeta())
{
    SetMod(prime);
    auto termsSet = dg.GetTerms();
    terms.assign(termsSet.begin(), termsSet.end());
    
    N = dg.GetTermsSize();
    f.resize(N);
    g.resize(N);
    a.resize(N);

    SetA(val_a);

    srand(seed);

    auto V = Vandermonde(a, terms);
    auto [IsInv, Rev] = V.Inverse();
    while (not IsInv) {
        SetARandom();
        V = Vandermonde(a, terms);
        tie(IsInv, Rev) = V.Inverse();
    }
    ReverseVdm = Rev;
}

Coder::Coder(int K, int L, int T, int prime, int seed) : K(K), L(L), T(T), dg(DegreeTable(K, L, T)), Adegrees(dg.GetAlpha()), Bdegrees(dg.GetBeta())
{
    SetMod(prime);
    auto termsSet = dg.GetTerms();
    terms.assign(termsSet.begin(), termsSet.end());
    
    
    N = dg.GetTermsSize();
    f.resize(N);
    g.resize(N);
    a.resize(N);

    srand(seed);

    auto V = Vandermonde(a, terms);
    auto [IsInv, Rev] = V.Inverse();
    while (not IsInv) {
        SetARandom();
        V = Vandermonde(a, terms);
        tie(IsInv, Rev) = V.Inverse();
    }
    ReverseVdm = Rev;
}

void Coder::Code(const Matrix& A, const Matrix& B){
    const auto [ma, na] = A.GetSize();
    const auto [mb, nb] = B.GetSize();

    if (a.size() != N)
        throw invalid_argument("evaluation vector supplied has wrong number of points");

    if (na != mb)
    {
        throw invalid_argument("matrix dimensions incompatible");
    }


    vector<Matrix> R (T, Matrix(ma/K, na, mod));
    vector<Matrix> S (T, Matrix(mb, nb/L, mod));
    for(auto& elem : R){
        elem.FillRandomly();
    }
    for(auto& elem : S){
        elem.FillRandomly();
    }

    for(int i = 0; i < N; i++){
        auto temp = R[T - 1];
        for (int k = K + T - 2; k > -1; k--)
        {
            if (k > K - 1)
            {
                temp = R[k-K] + temp * (a[i]^(Adegrees[k+1] - Adegrees[k]));
            }
            else
            {
                temp = A.GetBlock(k, K, PART_VERTICAL) + temp * (a[i]^(Adegrees[k+1] - Adegrees[k]));
            }
            
        }
        temp = temp * (a[i]^(Adegrees[0]));
        f[i] = temp;

        temp = S[T - 1];
        for (int l = L + T - 2; l > -1; l--)
        {
            if (l > L - 1)
            {
                temp = S[l-L] + temp * (a[i]^(Bdegrees[l+1] - Bdegrees[l]));
            }
            else
            {
                temp = B.GetBlock(l, L, PART_HORIZONTAL) + temp * (a[i]^(Bdegrees[l+1] - Bdegrees[l]));
            }
            
        }
        temp = temp * (a[i]^(Bdegrees[0]));
        g[i] = temp;
    }

    DegMatr.resize(K + T, vector<int>(L + T));
    const auto &temp_matr = dg.GetMatr();
    for (int k = 0; k < K + T; k++)
    {
        for (int l = 0; l < L + T; l++)
        {
            // NOT CORRECT!!!
            DegMatr[k][l] = temp_matr[k][l];
        }
    }
}

const vector<Matrix> &Coder::GetF() const{
    return f;
}

const vector<Matrix> &Coder::GetG() const{
    return g;
}

const vector<int> &Coder::GetTerms() const{
    return terms;
}

const vector<IntModuloP> &Coder::GetA() const{
    return a;
}

void Coder::SetA(vector<IntModuloP> &val){
    for (int i = 0; i < N; i++)
    {
        a[i] = val[i];
    }
}

void Coder::SetARandom(){
    // Floyd's algorithm for generation of a vector of unique numbers.
    map<int, bool> is_used;
    int in, im;

    im = 0;

    for (in = mod - N; in < mod && im < N; ++in) {
        int r = rand() % (in + 1); /* generate a random number 'r' */

        if (is_used[r]){
            /* we already have 'r' */
            r = in; /* use 'in' instead of the generated number */
        }

        assert(!is_used[r]);
        a[im++] = IntModuloP(mod, r);
        is_used[r] = 1;
    }

    assert(im == N);
}

const int &Coder::GetN() const{
    return N;
}

void Coder::SetMod(int prime){
    mod = prime;
}

const Matrix &Coder::GetReverseVdm() const {
    return ReverseVdm;
}

const vector<vector<int>> &Coder::GetDegMatr() const {
    return DegMatr;
}
