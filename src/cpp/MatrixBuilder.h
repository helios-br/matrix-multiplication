#ifndef MATRIX_BUILDER_H
#define MATRIX_BUILDER_H

#include <iostream>
#include "InstanceData.h"

using namespace std;

inline short **createPopulatedMatrix(int matrixOrder, int minValue, int maxValue)
{
	short **matrix = new short *[matrixOrder];
	for (int i = 0; i < matrixOrder; i++)
	{
		matrix[i] = new short[matrixOrder];
		for (int j = 0; j < matrixOrder; j++)
		{
			matrix[i][j] = minValue + (std::rand() % (maxValue - minValue + 1));
		}
	}
	return matrix;
}

inline short **createEmptyMatrix(int order)
{
	short **matrix = new short *[order];
	for (int i = 0; i < order; i++)
		matrix[i] = new short[order];
	return matrix;
}

inline void populateMatrix(short **matrix, int matrixOrder, int minValue, int maxValue)
{
	for (int i = 0; i < matrixOrder; i++)
		for (int j = 0; j < matrixOrder; j++)
			matrix[i][j] = minValue + (std::rand() % (maxValue - minValue + 1));
}

inline void deleteMatrix(short **matrix, int matrixOrder)
{
	for (int i = 0; i < matrixOrder; i++)
		delete[] matrix[i];
	delete[] matrix;
}

inline void printMatrix(short **matrix, int matrixOrder)
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

inline void printMatrixElementsSm(short **matrix, int matrixOrder)
{
	int total = 0;

	for (int i = 0; i < matrixOrder; i++)
		for (int j = 0; j < matrixOrder; j++)
			total += matrix[i][j];
			
	fprintf(stderr, "%5d\n", total);
}

#endif