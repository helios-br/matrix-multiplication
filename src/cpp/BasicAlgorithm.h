#ifndef BASIC_ALGORITHM_H
#define BASIC_ALGORITHM_H

#include <iostream>
#include "MatrixMultiplication.h"
#include "InstanceData.h"

using namespace std;

class BasicAlgorithm : public MatrixMultiplication
{
public:
    BasicAlgorithm() {}
    ~BasicAlgorithm() {}
    void execute(short **firstMatrix, short **secondMatrix, int order);
};

#endif