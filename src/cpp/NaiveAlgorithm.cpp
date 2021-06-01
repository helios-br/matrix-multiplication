#include "NaiveAlgorithm.h"

#include <iostream>
#include <omp.h>
#include "MatrixBuilder.h"

using namespace std;

vector<vector<int>> NaiveAlgorithm::multiply(vector<vector<int>>& firstMatrix, vector<vector<int>>& secondMatrix, int order)
{
	vector<vector<int>> resultMatrix (order, vector<int>(order));

	int i, j, k;

	#pragma omp parallel for private(i, j, k)
	for (i = 0; i < order; i++)
		for (j = 0; j < order; j++)
			for (k = 0; k < order; k++)
				resultMatrix[i][j] += firstMatrix[i][k] * secondMatrix[k][j];

	return resultMatrix;
};