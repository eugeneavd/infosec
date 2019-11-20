#ifndef INFOSEC_INTMODULOP_H
#define INFOSEC_INTMODULOP_H

typedef int IntModuloP;

class IntModuloP
{
private:
    int p;
    int z;
public:
    IntModuloP() = default;
    IntModuloP(int a);
    ~IntModuloP();
    friend IntModuloP operator + (const IntModuloP &a, const IntModuloP &b);
    friend IntModuloP operator - (const IntModuloP &a, const IntModuloP &b);
    friend IntModuloP operator * (const IntModuloP &a, const IntModuloP &b);
    friend IntModuloP operator / (const IntModuloP &a, const IntModuloP &b);
    friend IntModuloP Inverse (const IntModuloP &a);
};

IntModuloP::IntModuloP(int a)
{
}

IntModuloP::~IntModuloP()
{
}




#endif //INFOSEC_INTMODULOP_H
