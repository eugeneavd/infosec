#include <iostream>
#include <vector>
#include "../Matrix.h"
#include "../IntModuloP.h"

using namespace std;

int main() {
    const int prime = 73;
    const IntModuloP one = IntModuloP(prime, 1);
    IntModuloP x(73, 0);
    cin >> x;
    cout << one / x;
}
