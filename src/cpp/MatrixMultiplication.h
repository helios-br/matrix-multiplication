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
        virtual vector<vector<int>> multiply(vector<vector<int>>& firstMatrix, vector<vector<int>>& secondMatrix, int order) = 0;
};

#endif