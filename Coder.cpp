#include <iostream>
#include <iomanip>
#include "Matrix.h"
#include "DegreeTable.h"
#include "Coder.h"

Coder::Coder(Matrix A, Matrix B, int K, int L, int T) : K(K), L(L), T(T)
{
    const auto dg = DegreeTable(K, L, T);
    // почему const auto, а не const auto&
    const auto Adegrees = dg.GetAlpha();
    const auto Bdegrees = dg.GetBeta();
    const auto [ma, na] = A.GetSize();
    const auto [mb, nb] = B.GetSize();
    const auto mod = A.GetMod();
    terms = dg.GetTerms();
    
    vector<Matrix> R (T, Matrix(ma/K, na, mod));
    vector<Matrix> S (T, Matrix(mb, nb/L, mod));
    N = dg.GetTermsSize();
    f.resize(N);
    g.resize(N);
    vector<IntModuloP> x(N);

    for (int i = 0; i < N; i++)
    {
        // переменная ind не нужна
        IntModuloP ind(mod, i);
        x[i] = ind;
    }
    
    // vector<Matrix> f(N), g(N);
    for(int i = 0; i < N; i++){
        auto temp = R[T - 1];
        for (int k = K + T - 1; k > -1; k--)
        {
            if (k > K)
            {
                // segfault на первой итерации
                // неверная логика программы
                // коэфф. R[T-1] встречается два раза
                temp = R[k-K] + temp * (x[i]^(Adegrees[k+1] - Adegrees[k]));
            }
            else
            {
                temp = A.GetBlock(k, K, PART_VERTICAL) + temp * (x[i]^(Adegrees[k+1] - Adegrees[k]));
            }
            
        }
        const auto val1 = temp;

        temp = S[T - 1];
        for (int l = L + T - 1; l > -1; l--)
        {
            if (l > L)
            {
                temp = S[l-L] + temp * (x[i]^(Adegrees[l+1] - Adegrees[l]));
            }
            else
            {
                temp = B.GetBlock(l, L, PART_HORIZONTAL) + temp * (x[i]^(Adegrees[l+1] - Adegrees[l]));
            }
            
        }
        // переменные val1, val2 не нужны
        const auto val2 = temp;
        f[i] = val1;
        g[i] = val2;
    }
}

const vector<Matrix> &Coder::GetF() const{
    return f;
}

const vector<Matrix> &Coder::GetG() const{
    return g;
}

const set<int> &Coder::GetTerms() const{
    return terms;
}
