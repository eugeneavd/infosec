#include "../Matrix.h"
#include "../IntModuloP.h"
#include "../Coder.h"
#include "../Decoder.h"
#include <iostream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

int main() {
    const auto prime = 73;
    vector<IntModuloP> a(11);
    for (int i = 0; i < 11; i++)
        a[i] = IntModuloP(prime, i);
    //Coder c(2, 3, 1, a, prime);
    Coder c(2, 3, 1, prime);

    auto A = Matrix(6, 2, prime);
    auto B = Matrix(2, 6, prime);
    ifstream file;
    file.open("mat.txt");
    file >> A;
    file >> B;


    c.Code(A, B);
    const auto f = c.GetF();
    const auto g = c.GetG();
    const int N = c.GetN();
    auto h = vector<Matrix> (N);
    for (int i = 0; i < N; i++)
        h[i] = f[i] * g[i];
    const auto deg = c.GetTerms();
    const auto coefs = interpolate(h, c.GetReverseVdm());
    const auto block2deg = c.GetDegMatr();
    map<int, int> deg2index;
    for (int i=0; i < N; i++)
        deg2index[deg[i]] = i;
    Matrix AB(6, 6, prime);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            AB.SetBlock(i, j, 2, 3, coefs[deg2index[block2deg[i][j]]]);
    if (AB == A*B)
        cout << "Wow, guys! Such a succ.";
    else
        cout << "Abort:SNAFU!!! I said, FUBAR";
    return 0;
}
