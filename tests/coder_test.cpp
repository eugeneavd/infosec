#include "../Coder.h"
#include <iostream>

int main(int argc, char const *argv[])
{
	const int mod = 73;
    const int K = 2;
    const int L = 2;
    const int T = 1;
    std::vector<IntModuloP> vec;
    for (int i = 0; i < 8; i++)
    {
        vec.push_back(IntModuloP(mod, i));
    }

    int seed = atoi(argv[1]);
    auto coder = Coder(K, L, T, mod, seed);
    // auto coder = Coder(K, L, T, vec, mod);    
    // coder.SetMod(mod);
    // auto test_vec = coder.GetA();

    // for(auto &elem: test_vec){
    //     std::cout << elem << std::endl;
    // }

    Matrix A = IdentityMatrix(2, mod);
    // Matrix B = IdentityMatrix(2, mod)*IntModuloP(mod, 3);
    Matrix B(2, 2, mod);
    B(0, 0) = IntModuloP(mod, 1);
    B(0, 1) = IntModuloP(mod, 2);
    B(1, 0) = IntModuloP(mod, 3);
    B(1, 1) = IntModuloP(mod, 4);
    // cout << A.GetMod() << " " << B.GetMod() << std::endl;
    coder.Code(A, B);
    const auto test_g = coder.GetG();

    for(auto &elem: test_g){
        cout << elem;
    }
    
    return 0;
}
