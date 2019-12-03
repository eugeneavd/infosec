/*
 * [1] https://arxiv.org/pdf/1812.09962.pdf
 */
#include <iomanip>
#include <iostream>
#include <algorithm>
#include "DegreeTable.h"

using namespace std;
DegreeTable::DegreeTable(int K, int L, int T) : K(K), L(L), T(T){
    if (T < min(K, L))
        GASPsmall();
    else
        GASPbig();
}

void DegreeTable::GASPbig() {
    alpha.resize(K + T);
    beta.resize(L + T);
    int k, l;
    // init alpha and beta according to
    // [1], def. 7
    for (int i = 0; i < K + T; i++) {
        k = i + 1;
        if (k <= K)
            alpha[i] = k - 1;
        else {
            const int t = k - K; // k = K + t
            alpha[i] = K * L + t - 1;
        }
    }
    for (int i = 0; i < L + T; i++) {
        l = i + 1;
        if (l <= L) {
            beta[i] = K * (l - 1);
        } else {
            const int t = l - L;  // l = L + t
            beta[i] = K * L + t - 1;
        }
    }
    if (K < L)
        alpha.swap(beta);

    // construct degree table
    // explicit construction of degree table is only for debug purposes
    //
    const int m = alpha.size();
    const int n = beta.size();
    a_outer_b = vector<vector<int>>(m, vector<int>(n));
    for (int i=0; i < m; i++)
        for (int j=0; j < n; j++)
            terms.insert(a_outer_b[i][j] = alpha[i] + beta[j]);
    std::cout << terms.size() << endl;
}

void DegreeTable::GASPsmall() {
    alpha.resize(K + T);
    beta.resize(L + T);
    int k, l;
    // init alpha and beta according to
    // [1], def. 8
    for (int i = 0; i < K + T; i++) {
        k = i + 1;
        if (k <= K)
            alpha[i] = k - 1;
        else {
            const int t = k - K; // k = K + t
            alpha[i] = K * L + K*(t - 1);
        }
    }
    for (int i = 0; i < L + T; i++) {
        l = i + 1;
        if (l <= L) {
            beta[i] = K * (l - 1);
        } else {
            const int t = l - L;  // l = L + t
            beta[i] = K * L + t - 1;
        }
    }
    if (K < L)
        alpha.swap(beta);

    // construct degree table
    // explicit construction of degree table is only for debug purposes
    const int m = alpha.size();
    const int n = beta.size();
    a_outer_b = vector<vector<int>>(m, vector<int>(n));
    for (int i=0; i < m; i++)
        for (int j=0; j < n; j++)
            terms.insert(a_outer_b[i][j] = alpha[i] + beta[j]);
}

const vector<int> &DegreeTable::GetAlpha() const{
    return alpha;
}

const vector<int> &DegreeTable::GetBeta() const{
    return beta;
}

ostream &operator<<(ostream &out, const DegreeTable &dg) {
    out << std::setfill(' ');
    for (const auto& row: dg.a_outer_b) {
        for (const auto &elem: row)
            out << std::setw(4) << elem;
        out << "\n";
    }
    return out;
}

const int DegreeTable::GetTermsSize() const{
    return terms.size();
}

const set<int> DegreeTable::GetTerms() const{
    return terms;
}