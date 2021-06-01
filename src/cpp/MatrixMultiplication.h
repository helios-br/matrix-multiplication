#ifndef MATRIX_MULTIPLICATION_H
#define MATRIX_MULTIPLICATION_H

#include "InstanceData.h"
#include <vector>

using namespace std;

class MatrixMultiplication
{
    public:
        MatrixMultiplication() {}
        virtual ~MatrixMultiplication() {}
        void execute(InstanceData instanceData);
        virtual vector<vector<int>> multiply(vector<vector<int>>& matrixA, vector<vector<int>>& matrixB, int order) = 0;
        virtual vector<vector<int>> multiply(vector<vector<int>>& matrixA, int ai, int aj, vector<vector<int>>& matrixB, int bi, short bj, int order) = 0;
};

#endif