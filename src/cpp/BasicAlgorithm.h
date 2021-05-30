#ifndef BASIC_ALGORITHM_H
#define BASIC_ALGORITHM_H

#include "MatrixMultiplication.h"

class BasicAlgorithm : public MatrixMultiplication
{
    public:
        BasicAlgorithm() {}
        ~BasicAlgorithm() {}
        short **multiply(short **firstMatrix, short **secondMatrix, int order);
};

#endif