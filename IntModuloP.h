#include <iostream>
#include <exception>
#ifndef INFOSEC_INTMODULOP_H
#define INFOSEC_INTMODULOP_H


class IntModuloP {
public:
    IntModuloP (int mod, int value);
    friend IntModuloP operator+(const IntModuloP& x, const IntModuloP& y);
    friend IntModuloP operator-(const IntModuloP& x, const IntModuloP& y);
    friend IntModuloP operator*(const IntModuloP& x, const IntModuloP& y);
    friend IntModuloP operator/(const IntModuloP& x, const IntModuloP& y);
    friend std::ostream& operator<<(std::ostream& out, const IntModuloP& x);
    friend std::istream& operator>>(std::istream& in, IntModuloP& x);
    // convert to int
    explicit operator int() const;
private:
    int mod;
    int value;
};

IntModuloP operator+(const IntModuloP& x, const IntModuloP& y);
IntModuloP operator-(const IntModuloP& x, const IntModuloP& y);
IntModuloP operator*(const IntModuloP& x, const IntModuloP& y);
IntModuloP operator/(const IntModuloP& x, const IntModuloP& y);

std::ostream& operator<<(std::ostream& out, const IntModuloP& x);
std::istream& operator>>(std::istream& in, IntModuloP& x);

int gcd (int a, int b, int & x, int & y);
#endif //INFOSEC_INTMODULOP_H
