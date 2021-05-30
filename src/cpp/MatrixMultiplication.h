#ifndef MATRIX_MULTIPLICATION_H
#define MATRIX_MULTIPLICATION_H

#include "InstanceData.h"

using namespace std;

class MatrixMultiplication
{
    public:
        MatrixMultiplication() {}
        virtual ~MatrixMultiplication() {}
        void execute(InstanceData instanceData);
        virtual short **multiply(short **firstMatrix, short **secondMatrix, int order) = 0;
};

#endif