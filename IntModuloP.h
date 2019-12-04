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
    friend bool operator==(const IntModuloP &lhs, const IntModuloP &rhs);
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
IntModuloP operator^(const IntModuloP& x, int n);

std::ostream& operator<<(std::ostream& out, const IntModuloP& x);
std::istream& operator>>(std::istream& in, IntModuloP& x);
bool operator==(const IntModuloP &lhs, const IntModuloP &rhs);

int gcd (int a, int b, int & x, int & y);
#endif //INFOSEC_INTMODULOP_H
