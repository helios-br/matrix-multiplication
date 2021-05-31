#include "StrassenAlgorithm.h"

#include <iostream>
#include <omp.h>
#include "MatrixBuilder.h"
#include "MatrixOperations.h"

using namespace std;

vector<vector<int>> StrassenAlgorithm::multiply(vector<vector<int>> firstMatrix, vector<vector<int>> secondMatrix, int order)
{
	if (order == 1)
	{
		return this->naiveMultiplication->multiply(firstMatrix, secondMatrix, order);
	}

	int newOrder = order / 2;

	// Creates partitions for input matrices

	vector<vector<int>> firstMatrix11 = createEmptyMatrix(newOrder);
	vector<vector<int>> firstMatrix12 = createEmptyMatrix(newOrder);
	vector<vector<int>> firstMatrix21 = createEmptyMatrix(newOrder);
	vector<vector<int>> firstMatrix22 = createEmptyMatrix(newOrder);

	vector<vector<int>> secondMatrix11 = createEmptyMatrix(newOrder);
	vector<vector<int>> secondMatrix12 = createEmptyMatrix(newOrder);
	vector<vector<int>> secondMatrix21 = createEmptyMatrix(newOrder);
	vector<vector<int>> secondMatrix22 = createEmptyMatrix(newOrder);

	for (int i = 0; i < newOrder; i++)
	{
		for (int j = 0; j < newOrder; j++)
		{
			firstMatrix11[i][j] = firstMatrix[i][j];
			firstMatrix12[i][j] = firstMatrix[i][newOrder + j];
			firstMatrix21[i][j] = firstMatrix[newOrder + i][j];
			firstMatrix22[i][j] = firstMatrix[newOrder + i][newOrder + j];
			secondMatrix11[i][j] = secondMatrix[i][j];
			secondMatrix12[i][j] = secondMatrix[i][newOrder + j];
			secondMatrix21[i][j] = secondMatrix[newOrder + i][j];
			secondMatrix22[i][j] = secondMatrix[newOrder + i][newOrder + j];
		}
	}

	// Creates "M" matrices based on the partitions

	vector<vector<int>> m1 = this->multiply(add(firstMatrix11, firstMatrix22, newOrder), add(secondMatrix11, secondMatrix22, newOrder), newOrder);
	vector<vector<int>> m2 = this->multiply(add(firstMatrix21, firstMatrix22, newOrder), secondMatrix11, newOrder);
	vector<vector<int>> m3 = this->multiply(firstMatrix11, subtract(secondMatrix12, secondMatrix22, newOrder), newOrder);
	vector<vector<int>> m4 = this->multiply(firstMatrix22, subtract(secondMatrix21, secondMatrix11, newOrder), newOrder);
	vector<vector<int>> m5 = this->multiply(add(firstMatrix11, firstMatrix12, newOrder), secondMatrix22, newOrder);	
	vector<vector<int>> m6 = this->multiply(subtract(firstMatrix21, firstMatrix11, newOrder), add(secondMatrix11, secondMatrix12, newOrder), newOrder);	
	vector<vector<int>> m7 = this->multiply(subtract(firstMatrix12, firstMatrix22, newOrder), add(secondMatrix21, secondMatrix22, newOrder), newOrder);

	// Result matrix

	vector<vector<int>> c11 = add(subtract(add(m1, m4, newOrder), m5, newOrder), m7, newOrder);
	vector<vector<int>> c12 = add(m3, m5, newOrder);
	vector<vector<int>> c21 = add(m2, m4, newOrder);
	vector<vector<int>> c22 = add(add(subtract(m1, m2, newOrder), m3, newOrder), m6, newOrder);

	vector<vector<int>> resultMatrix = createEmptyMatrix(order);

	for (int i = 0; i < newOrder; i++)
	{
		for (int j = 0; j < newOrder; j++)
		{
			resultMatrix[i][j] = c11[i][j];
			resultMatrix[i][j + newOrder] = c12[i][j];
			resultMatrix[newOrder + i][j] = c21[i][j];
			resultMatrix[newOrder + i][newOrder + j] = c22[i][j];
		}
	}

	return resultMatrix;
};

/* vector<vector<int>> StrassenAlgorithm::multiply(vector<vector<int>> firstMatrix, vector<vector<int>> secondMatrix, int order)
{
	if (order == 1)
	{
		return this->naiveMultiplication->multiply(firstMatrix, secondMatrix, order);
	}

	int newOrder = order / 2;

	// Creates partitions for input matrices

	vector<vector<int>> firstMatrix11 = createEmptyMatrix(newOrder);
	vector<vector<int>> firstMatrix12 = createEmptyMatrix(newOrder);
	vector<vector<int>> firstMatrix21 = createEmptyMatrix(newOrder);
	vector<vector<int>> firstMatrix22 = createEmptyMatrix(newOrder);

	vector<vector<int>> secondMatrix11 = createEmptyMatrix(newOrder);
	vector<vector<int>> secondMatrix12 = createEmptyMatrix(newOrder);
	vector<vector<int>> secondMatrix21 = createEmptyMatrix(newOrder);
	vector<vector<int>> secondMatrix22 = createEmptyMatrix(newOrder);

	for (int i = 0; i < newOrder; i++)
	{
		for (int j = 0; j < newOrder; j++)
		{
			firstMatrix11[i][j] = firstMatrix[i][j];
			firstMatrix12[i][j] = firstMatrix[i][newOrder + j];
			firstMatrix21[i][j] = firstMatrix[newOrder + i][j];
			firstMatrix22[i][j] = firstMatrix[newOrder + i][newOrder + j];
			secondMatrix11[i][j] = secondMatrix[i][j];
			secondMatrix12[i][j] = secondMatrix[i][newOrder + j];
			secondMatrix21[i][j] = secondMatrix[newOrder + i][j];
			secondMatrix22[i][j] = secondMatrix[newOrder + i][newOrder + j];
		}
	}

	// Creates "M" matrices based on the partitions

	vector<vector<int>> m1 = this->multiply(add(firstMatrix11, firstMatrix22, newOrder), add(secondMatrix11, secondMatrix22, newOrder), newOrder);
	vector<vector<int>> m2 = this->multiply(add(firstMatrix21, firstMatrix22, newOrder), secondMatrix11, newOrder);
	vector<vector<int>> m3 = this->multiply(firstMatrix11, subtract(secondMatrix12, secondMatrix22, newOrder), newOrder);
	vector<vector<int>> m4 = this->multiply(firstMatrix22, subtract(secondMatrix21, secondMatrix11, newOrder), newOrder);
	vector<vector<int>> m5 = this->multiply(add(firstMatrix11, firstMatrix12, newOrder), secondMatrix22, newOrder);	
	vector<vector<int>> m6 = this->multiply(subtract(firstMatrix21, firstMatrix11, newOrder), add(secondMatrix11, secondMatrix12, newOrder), newOrder);	
	vector<vector<int>> m7 = this->multiply(subtract(firstMatrix12, firstMatrix22, newOrder), add(secondMatrix21, secondMatrix22, newOrder), newOrder);

	// Result matrix

	vector<vector<int>> c11 = add(subtract(add(m1, m4, newOrder), m5, newOrder), m7, newOrder);
	vector<vector<int>> c12 = add(m3, m5, newOrder);
	vector<vector<int>> c21 = add(m2, m4, newOrder);
	vector<vector<int>> c22 = add(add(subtract(m1, m2, newOrder), m3, newOrder), m6, newOrder);

	vector<vector<int>> resultMatrix = createEmptyMatrix(order);

	for (int i = 0; i < newOrder; i++)
	{
		for (int j = 0; j < newOrder; j++)
		{
			resultMatrix[i][j] = c11[i][j];
			resultMatrix[i][j + newOrder] = c12[i][j];
			resultMatrix[newOrder + i][j] = c21[i][j];
			resultMatrix[newOrder + i][newOrder + j] = c22[i][j];
		}
	}

	return resultMatrix;
}; */