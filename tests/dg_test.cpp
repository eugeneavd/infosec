#include "../DegreeTable.h"
#include <iostream>

int main() {
    std::cout << DegreeTable(3, 3, 2) << DegreeTable(3, 3, 2).GetTermsSize() << std::endl;
    return 0;
}