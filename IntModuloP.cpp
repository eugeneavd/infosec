#include "IntModuloP.h"
#include <limits>

int gcd(int a, int b, int & x, int & y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    int x1, y1;
    int d = gcd (b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

IntModuloP operator/(const IntModuloP &x, const IntModuloP &y) {
    int p, q;
    gcd(y.value, static_cast<int> (y.mod), p, q);
    while (p < 0) p += y.mod;
    return x * IntModuloP(y.mod, p);
}

IntModuloP operator*(const IntModuloP &x, const IntModuloP &y) {
    if (x.mod != y.mod){
        // std::cout << x.mod << " " << y.mod << std::endl;
        throw std::invalid_argument("Moduli are't equal");
    }
    return IntModuloP(x.mod, x.value * y.value);
}

std::ostream& operator<<(std::ostream& out, const IntModuloP& x) {
    out << x.value;
    return out;
}

std::istream& operator>>(std::istream& in, IntModuloP& x) {
    in >> x.value;
    while (x.value < 0) x.value += x.mod;
    x.value = x.value % x.mod;
    return in;
}

IntModuloP operator+(const IntModuloP& x, const IntModuloP& y) {
    if (x.mod != y.mod) throw std::invalid_argument("Moduli are't equal");
    return IntModuloP(x.mod, x.value + y.value);
}

IntModuloP::IntModuloP(int mod, int value) : mod(mod), value(value) {
    if (mod <= 0 ) {
        // std::cout << mod << " " << value << std::endl;
        throw std::invalid_argument("Modulus must be positive");
    }
    while (value < 0) value += mod;
    this->value = value % mod;
}

IntModuloP operator-(const IntModuloP& x, const IntModuloP& y) {
    if (x.mod != y.mod) throw std::invalid_argument("Moduli are't equal");
    return IntModuloP(x.mod, x.value - y.value);
}

IntModuloP operator^(const IntModuloP &x, int n) {
    // std::cout << x.GetMod() << " " << x << std::endl;
    if (n < 0) throw std::invalid_argument("Negative degree");
    if ((n % 2) != 0) {
        return x * (x^(n-1));
    } else if (n == 0) {
        // return IntModuloP(mod, 1);
        return IntModuloP(x.GetMod(), 1);
    } else {
        IntModuloP temp = x^(n/2);
        return temp * temp;
    }
}

bool operator==(const IntModuloP &lhs, const IntModuloP &rhs) {
    return lhs.value == rhs.value;
}

IntModuloP::operator int() const {
    return value;
}

int IntModuloP::GetMod() const {
    return mod;
}

IntModuloP::IntModuloP() {
    mod = std::numeric_limits<int>::max();
    value = 0;
}
