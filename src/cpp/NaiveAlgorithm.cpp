#include "NaiveAlgorithm.h"

#include <iostream>
#include <omp.h>
#include "MatrixBuilder.h"

using namespace std;

vector<vector<int>> NaiveAlgorithm::multiply(vector<vector<int>>& matrixA, vector<vector<int>>& matrixB, int order)
{
	vector<vector<int>> resultMatrix (order, vector<int>(order));

	int i, j, k;

	#pragma omp parallel for private(i, j, k)
	for (i = 0; i < order; i++)
		for (j = 0; j < order; j++)
			for (k = 0; k < order; k++)
				resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];

	return resultMatrix;
};

vector<vector<int>> NaiveAlgorithm::multiply(vector<vector<int>>& matrixA, int ai, int aj, vector<vector<int>>& matrixB, int bi, short bj, int order)
{
	vector<vector<int>> resultMatrix (order, vector<int>(order));

	int i, j, k;

	cout << "matrix a size: " << matrixA.size() << ", b size: " << matrixB.size() << endl;

	#pragma omp parallel for private(i, j, k)
	for (i = 0; i < order; i++)
		for (j = 0; j < order; j++)
			for (k = 0; k < order; k++)
				resultMatrix[i][j] += matrixA[i + ai][k + aj] * matrixB[k + bi][j + bj];

	return resultMatrix;
}