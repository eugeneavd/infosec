#include<vector>
#include "Matrix.h"
#include "DegreeTable.h"

#ifndef INFOSEC_CODER_H
#define INFOSEC_CODER_H

class Coder
{
private:
    const int K, L, T;
    
public:
    Coder(Matrix A, Matrix B, int K, int L, int T);
};



#endif //INFOSEC_CODER_H