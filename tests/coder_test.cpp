#include "../Coder.h"
#include <iostream>

int main(int argc, char const *argv[])
{
	const int mod = 23;

    std::vector<IntModuloP> vec;
    for (int i = 0; i < 18; i++)
    {
        vec.push_back(IntModuloP(mod, i));
    }
    
    auto coder = Coder(3, 3, 2, vec);
    // auto test_vec = coder.GetA();

    // for(auto &elem: test_vec){
    //     std::cout << elem << std::endl;
    // }

    Matrix A = IdentityMatrix(3, mod);
    Matrix B = IdentityMatrix(3, mod)*IntModuloP(mod, 3);
    // cout << A.GetMod() << " " << B.GetMod() << std::endl;
    coder.Code(A, B);
    
    return 0;
}
