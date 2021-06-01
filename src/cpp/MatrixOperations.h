#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "MatrixBuilder.h"
#include <vector>

inline vector<vector<int>> add(vector<vector<int>> &matrixA, vector<vector<int>> &matrixB, int order)
{
	vector<vector<int>> resultMatrix(order, vector<int>(order));

	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			resultMatrix[i][j] = matrixA[i][j] + matrixB[i][j];
		}
	}

	return resultMatrix;
}

inline vector<vector<int>> add(vector<vector<int>> &matrixA, short ai, short aj, vector<vector<int>> &matrixB, short bi, short bj, int order)
{
	vector<vector<int>> resultMatrix(order, vector<int>(order));

	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			resultMatrix[i][j] = matrixA[i + ai][j + aj] + matrixB[i + bi][j + bj];
		}
	}

	return resultMatrix;
}

inline void add(vector<vector<int>> &matrixA, vector<vector<int>> &matrixB, int order, vector<vector<int>> &resultMatrix)
{
	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
			resultMatrix[i][j] = matrixA[i][j] + matrixB[i][j];
}

inline vector<vector<int>> subtract(vector<vector<int>> &matrixA, vector<vector<int>> &matrixB, int order)
{
	vector<vector<int>> resultMatrix(order, vector<int>(order));

	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
			resultMatrix[i][j] = matrixA[i][j] - matrixB[i][j];

	return resultMatrix;
}

inline vector<vector<int>> subtract(vector<vector<int>> &matrixA, short ai, short aj, vector<vector<int>> &matrixB, short bi, short bj, int order)
{
	vector<vector<int>> resultMatrix(order, vector<int>(order));

	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			resultMatrix[i][j] = matrixA[i + ai][j + aj] - matrixB[i + bi][j + bj];
		}
	}

	return resultMatrix;
}

inline void subtract(vector<vector<int>> &matrixA, vector<vector<int>> &matrixB, int order, vector<vector<int>> &resultMatrix)
{
	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
			resultMatrix[i][j] = matrixA[i][j] - matrixB[i][j];
}

inline unsigned long long sumAllElements(vector<vector<int>> &matrix, int order)
{
	unsigned long long total = 0;
	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
			total += matrix[i][j];
	return total;
}

#endif