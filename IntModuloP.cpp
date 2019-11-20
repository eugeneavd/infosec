#include "IntModuloP.h"
#include "includes.h"

IntModuloP operator + (const IntModuloP &a, const IntModuloP &b){
    IntModuloP res;
    res.z = (a.z + b.z) % a.p;
}

IntModuloP operator - (const IntModuloP &a, const IntModuloP &b){
    IntModuloP res;
    res.z = (a.z - b.z) % a.p;
}

