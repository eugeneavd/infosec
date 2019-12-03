#include<vector>
#include "Matrix.h"
#include "DegreeTable.h"

#ifndef INFOSEC_CODER_H
#define INFOSEC_CODER_H

class Coder
{
private:
    const int K, L, T;
    vector<Matrix> f, g;
    // DegreeTable dg;
    int N;
    set<int> terms {};
    
public:
    Coder(Matrix A, Matrix B, int K, int L, int T);
    const vector<Matrix> &GetF() const;
    const vector<Matrix> &GetG() const;
    const set<int> &GetTerms() const;
};


#endif //INFOSEC_CODER_H