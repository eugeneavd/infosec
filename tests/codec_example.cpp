#include "../Matrix.h"
#include "../IntModuloP.h"
#include "../Coder.h"
#include "../Decoder.h"
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    const auto prime = 73;
    vector<IntModuloP> a(8);
    for (int i = 0; i < 8; i++)
        a[i] = IntModuloP(prime, i);
    Coder c(2, 2, 1, a, prime);

    auto A = Matrix(2, 2, prime);
    auto B = Matrix(2, 2, prime);
    A(0, 0) = IntModuloP(73, 1);
    A(0, 1) = IntModuloP(73, 2);
    A(1, 0) = IntModuloP(73, 3);
    A(1, 1) = IntModuloP(73, 4);
    B(0, 0) = IntModuloP(73, 7);
    B(0, 1) = IntModuloP(73, 8);
    B(1, 0) = IntModuloP(73, 9);
    B(1, 1) = IntModuloP(73, 10);

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
    // SANITY CHECK HERE!!! OH.. SHIT!!
    // degs are 0, 1, 4
    // R = f(0)
    Matrix S(2, 1, prime);
    S(0, 0) = c.GetF()[0](0, 0);
    S(1, 0) = c.GetF()[0](0, 1);
    auto b_deg = DegreeTable(2, 2, 1).GetBeta();
    Matrix TESTG1(2, 1, prime);
    cout << S;
    cout << "hui" << endl;
    TESTG1 = B.GetBlock(0, 2, PART_HORIZONTAL) * (a[1]^b_deg[0]) +
            B.GetBlock(1, 2, PART_HORIZONTAL) * (a[1]^b_deg[1]) +
            S * (a[1]^b_deg[2]);
    cout << a[1] << endl;
    cout << "TESTF1 (fuck dat shit)" << endl;
    cout << TESTG1;
    cout << "hui2" << endl;
    cout << g[1] << endl;

    Matrix AB(2, 2, prime);
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            AB.SetBlock(i, j, 2, 2, coefs[deg2index[block2deg[i][j]]]);
    return 0;
}
