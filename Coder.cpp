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
    termsSet = dg.GetTerms();
    terms.assign(termsSet.begin(), termsSet.end());
    
    N = dg.GetTermsSize();
    f.resize(N);
    g.resize(N);
    a.resize(N);

    /*
     * Alas, code repetition be again!! Thou have a ::SetA function
     */
    SetA(val_a);
}

Coder::Coder(int K, int L, int T, int prime, int seed) : K(K), L(L), T(T), dg(DegreeTable(K, L, T)), Adegrees(dg.GetAlpha()), Bdegrees(dg.GetBeta())
{
    SetMod(prime);
    termsSet = dg.GetTerms();
    terms.assign(termsSet.begin(), termsSet.end());
    
    
    N = dg.GetTermsSize();
    f.resize(N);
    g.resize(N);
    a.resize(N);

    SetARandom(seed);
}

void Coder::Code(Matrix A, Matrix B){
    // mod = A.GetMod();
    const auto [ma, na] = A.GetSize();
    const auto [mb, nb] = B.GetSize();

    if (na != mb)
    {
        throw invalid_argument("matrix dimensions incompatible");
    }
    // vector<int> vec;
    // vec.assign(terms.begin(), terms.end());     // fill vec with values from terms

    /*
     * NB: V might be uninvertable so we might need to generate vector a again.
     */
    auto V = Vandermonde(a, terms);
    auto [IsInv, Rev] = V.Inverse();
    while (not IsInv) {
        SetARandom();
        V = Vandermonde(a, terms);
        tie(IsInv, Rev) = V.Inverse();
    }
    ReverseVdm = Rev;


    vector<Matrix> R (T, Matrix(ma/K, na, mod));
    vector<Matrix> S (T, Matrix(mb, nb/L, mod));
    for(auto& elem : R){
        elem.FillRandomly();
        // cout << elem << endl;
    }
    for(auto& elem : S){
        elem.FillRandomly();
        // cout << elem << endl;
    }

    for(int i = 0; i < N; i++){
        auto temp = R[T - 1];
        // cout << a[i] << endl;
        for (int k = K + T - 2; k > -1; k--)
        {
            if (k > K - 1)
            {
                temp = R[k-K] + temp * (a[i]^(Adegrees[k+1] - Adegrees[k]));
                // cout << temp << endl;
            }
            else
            {
                temp = A.GetBlock(k, K, PART_VERTICAL) + temp * (a[i]^(Adegrees[k+1] - Adegrees[k]));
                // cout << temp << endl;
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
    // cout << "Degree matrix:\n";
    // for(auto &row : DegMatr){
    //     for(auto &elem: row){
    //         cout << elem << "\t";
    //     }
    //     cout << endl;
    // }
}

const vector<Matrix> &Coder::GetF() const{
    return f;
}

const vector<Matrix> &Coder::GetG() const{
    return g;
}

vector<int> Coder::GetTerms() const{
    vector<int> vec;
    vec.assign(terms.begin(), terms.end());     // fill vec with values from terms
    sort(begin(vec), end(vec));
    return vec;
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

void Coder::SetARandom(int seed){
    /*
     * The Knuth algorithm is not optimal for our purpose.
     * Implement The Floyd algorithm!!!
     */
    // int in, im = 0;
    // srand(seed);

    // for (in = 0; in < mod && im < N; ++in) {
    //     int rn = mod - in;
    //     int rm = N - im;
    //     if (rand() % rn < rm)
    //         a[im++] = IntModuloP(mod, in);
    // }

    // cout << im << endl;
    // assert(im == N);

    map<int, bool> is_used;
    int in, im;

    im = 0;
    srand(seed);

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