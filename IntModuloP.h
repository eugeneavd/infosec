#include <iostream>
#ifndef INFOSEC_INTMODULOP_H
#define INFOSEC_INTMODULOP_H

// MOD is < unsigned int

class IntModuloP {
public:
    IntModuloP (unsigned int mod, unsigned int value) : mod(mod), value(value){};
    friend IntModuloP operator+(const IntModuloP& x, const IntModuloP& y);
    friend IntModuloP operator-(const IntModuloP& x, const IntModuloP& y);
    friend IntModuloP operator*(const IntModuloP& x, const IntModuloP& y);
    friend IntModuloP operator/(const IntModuloP& x, const IntModuloP& y);
    friend std::ostream& operator<<(std::ostream& out, const IntModuloP& x);
    friend std::istream& operator>>(std::istream& in, IntModuloP& x);
    // copy assigment
    IntModuloP& operator=(IntModuloP& );
    IntModuloP& operator=(const IntModuloP& );
    // convert to int
    operator int() const;
private:
    const unsigned int mod;
    unsigned int value;
};

IntModuloP operator+(const IntModuloP& x, const IntModuloP& y);
IntModuloP operator-(const IntModuloP& x, const IntModuloP& y);
IntModuloP operator*(const IntModuloP& x, const IntModuloP& y);
IntModuloP operator/(const IntModuloP& x, const IntModuloP& y);

std::ostream& operator<<(std::ostream& out, const IntModuloP& x);
std::istream& operator>>(std::istream& in, IntModuloP& x);

#endif //INFOSEC_INTMODULOP_H
