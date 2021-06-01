#ifndef MATRIX_BUILDER_H
#define MATRIX_BUILDER_H

#include <iostream>
#include <vector>
#include "InstanceData.h"

using namespace std;

inline vector<vector<int>> createPopulatedMatrix(int matrixOrder, int minValue, int maxValue)
{
	vector<vector<int>> matrix(matrixOrder, vector<int>(matrixOrder));

	for (int i = 0; i < matrixOrder; i++)
		for (int j = 0; j < matrixOrder; j++)
			matrix[i][j] = minValue + (std::rand() % (maxValue - minValue + 1));
	return matrix;
}

inline vector<vector<int>> createEmptyMatrix(int order)
{
	vector<vector<int>> matrix(order, vector<int>(order));
	return matrix;
}

inline void printMatrix(vector<vector<int>> &matrix, int matrixOrder)
{
	fprintf(stderr, "\n");
	for (int i = 0; i < matrixOrder; i++)
	{
		fprintf(stderr, " [");
		for (int j = 0; j < matrixOrder; j++)
		{
			fprintf(stderr, "%5d ", matrix[i][j]);
		}
		fprintf(stderr, "]\n");
	}
	fprintf(stderr, "\n");
}

inline void printMatrixElementsSum(vector<vector<int>> &matrix, int matrixOrder)
{
	unsigned long long total = 0;

	for (int i = 0; i < matrixOrder; i++)
		for (int j = 0; j < matrixOrder; j++)
			total += matrix[i][j];

	cout << "Result: " << total << endl;
}

#endif