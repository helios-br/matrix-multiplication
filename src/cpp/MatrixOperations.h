#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "MatrixBuilder.h"
#include <vector>

inline vector<vector<int>> add(vector<vector<int>> firstMatrix, vector<vector<int>> secondMatrix, int order)
{
	vector<vector<int>> resultMatrix (order, vector<int>(order));

	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			resultMatrix[i][j] = firstMatrix[i][j] + secondMatrix[i][j];
		}
	}

	return resultMatrix;
}

inline void add(vector<vector<int>> firstMatrix, vector<vector<int>> secondMatrix, int order, vector<vector<int>> &resultMatrix)
{
	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
			resultMatrix[i][j] = firstMatrix[i][j] + secondMatrix[i][j];
}

inline vector<vector<int>> subtract(vector<vector<int>> firstMatrix, vector<vector<int>> secondMatrix, int order)
{
	vector<vector<int>> resultMatrix (order, vector<int>(order));

	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
			resultMatrix[i][j] = firstMatrix[i][j] - secondMatrix[i][j];

	return resultMatrix;
}

inline void subtract(vector<vector<int>> firstMatrix, vector<vector<int>> secondMatrix, int order, vector<vector<int>> &resultMatrix)
{
	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
			resultMatrix[i][j] = firstMatrix[i][j] - secondMatrix[i][j];
}

inline unsigned long long sumAllElements(vector<vector<int>> matrix, int order)
{
	unsigned long long total = 0;
	for (int i = 0; i < order; i++)
		for (int j = 0; j < order; j++)
			total += matrix[i][j];
	return total;
}

#endif