#include "Decoder.h"

std::vector<Matrix> interpolate(const std::vector<Matrix> &h, const Matrix &invV) {
    const auto [m, n] = invV.GetSize();
    const auto [mino, nino] = h[0].GetSize();
    const int N = h.size();
    if (!((m == n) && (n == N))) throw std::invalid_argument("dimensions don't match");
    std::vector<Matrix> coefs(N, Matrix(mino, nino, invV.GetMod()));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            coefs[i] = coefs[i] + h[j] * invV(i, j);
    return coefs;
}
