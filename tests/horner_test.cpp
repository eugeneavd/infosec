#include <iostream>
#include <vector>
#include "../Matrix.h"
#include "../IntModuloP.h"

using namespace std;

int main() {
    const int K = 2;
    const int L = 2;
    const int T = 1;

    Matrix B(2, 2, 73);
    vector<Matrix> S = {Matrix(2, 1, 73)};
    S[0](0, 0) = IntModuloP(73, 7);
    S[0](1, 0) = IntModuloP(73, 8);
    vector<int> Bdegrees = {1, 3, 7};
    const auto a = IntModuloP(73, 2);

    B(0, 0) = IntModuloP(73, 1);
    B(0, 1) = IntModuloP(73, 2);
    B(1, 0) = IntModuloP(73, 3);
    B(1, 1) = IntModuloP(73, 4);

    auto temp = S[T - 1];
    for (int l = L + T - 2; l > -1; l--) {
        if (l > L - 1) {
            temp = S[l - L] + temp * (a ^ (Bdegrees[l + 1] - Bdegrees[l]));
        } else {
            temp = B.GetBlock(l, L, PART_HORIZONTAL) + temp * (a ^ (Bdegrees[l + 1] - Bdegrees[l]));
        }
        temp = temp * (a ^ (Bdegrees[0]));

    }
    cout << temp << endl;
}
