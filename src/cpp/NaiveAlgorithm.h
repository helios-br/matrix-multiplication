#ifndef NAIVE_ALGORITHM_H
#define NAIVE_ALGORITHM_H

#include "MatrixMultiplication.h"
#include <vector>

class NaiveAlgorithm : public MatrixMultiplication
{
    public:
        NaiveAlgorithm() {}
        ~NaiveAlgorithm() {}
        vector<vector<int>> multiply(vector<vector<int>>& matrixA, vector<vector<int>>& matrixB, int order);
        vector<vector<int>> multiply(vector<vector<int>>& matrixA, int ai, int aj, vector<vector<int>>& matrixB, int bi, short bj, int order);
};

#endif