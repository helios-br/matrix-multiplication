#ifndef BASIC_ALGORITHM_H
#define BASIC_ALGORITHM_H

#include "MatrixMultiplication.h"
#include <vector>

class BasicAlgorithm : public MatrixMultiplication
{
    public:
        BasicAlgorithm() {}
        ~BasicAlgorithm() {}
        vector<vector<int>> multiply(vector<vector<int>> firstMatrix, vector<vector<int>> secondMatrix, int order);
};

#endif