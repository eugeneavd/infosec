#include "../DegreeTable.h"
#include <iostream>

int main() {
    std::cout << DegreeTable(2, 2, 1) << DegreeTable(2, 2, 1).GetTermsSize() << std::endl;
    return 0;
}