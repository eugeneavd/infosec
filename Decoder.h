#ifndef INFOSEC_DECODER_H
#define INFOSEC_DECODER_H


#include <vector>
#include "Matrix.h"

class Decoder {

};

// given invV, interpolate polynom
// invV is calculated, when Coder chooses evaluation vector
std::vector<Matrix> interpolate(const std::vector<Matrix>& h, const Matrix& invV);

#endif //INFOSEC_DECODER_H
