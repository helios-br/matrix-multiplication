#ifndef NAIVE_ALGORITHM_H
#define NAIVE_ALGORITHM_H

#include "MatrixMultiplication.h"
#include <vector>

class NaiveAlgorithm : public MatrixMultiplication
{
    public:
        NaiveAlgorithm() {}
        ~NaiveAlgorithm() {}
        vector<vector<int>> multiply(vector<vector<int>>& firstMatrix, vector<vector<int>>& secondMatrix, int order);
};

#endif