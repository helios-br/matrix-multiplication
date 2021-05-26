#ifndef MATRIX_MULTIPLICATION_H
#define MATRIX_MULTIPLICATION_H

#include <iostream>
#include "InstanceData.h"

using namespace std;

class MatrixMultiplication
{
public:
    MatrixMultiplication() {}
    virtual ~MatrixMultiplication() {}
    virtual void execute(short **firstMatrix, short **secondMatrix, int order) = 0;
    InstanceData instanceData;
};

#endif