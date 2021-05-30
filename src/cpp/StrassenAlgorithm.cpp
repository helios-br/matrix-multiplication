#include "StrassenAlgorithm.h"

#include <iostream>
#include <omp.h>
#include "MatrixBuilder.h"
#include "BasicAlgorithm.h"
#include "MatrixOperations.h"

using namespace std;

vector<vector<int>> StrassenAlgorithm::multiply(vector<vector<int>> firstMatrix, vector<vector<int>> secondMatrix, int order)
{
	if (order == 1)
	{
		return this->basicMultiplication->multiply(firstMatrix, secondMatrix, order);
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

	/*vector<vector<int>> temp1 = createEmptyMatrix(newOrder);
	vector<vector<int>> temp2 = createEmptyMatrix(newOrder);
	vector<vector<int>> temp3 = createEmptyMatrix(newOrder);
	vector<vector<int>> temp4 = createEmptyMatrix(newOrder);
	vector<vector<int>> temp5 = createEmptyMatrix(newOrder);
	vector<vector<int>> temp6 = createEmptyMatrix(newOrder);
	vector<vector<int>> temp7 = createEmptyMatrix(newOrder);
	vector<vector<int>> temp8 = createEmptyMatrix(newOrder);
	vector<vector<int>> temp9 = createEmptyMatrix(newOrder);
	vector<vector<int>> temp10 = createEmptyMatrix(newOrder);

	temp1 = add(firstMatrix11, firstMatrix22, newOrder);
	temp2 = add(secondMatrix11, secondMatrix22, newOrder);
	vector<vector<int>>  m1 = this->multiply(temp1, temp2, newOrder);

	temp3 = add(firstMatrix21, firstMatrix22, newOrder);
	vector<vector<int>> m2 = this->multiply(temp3, secondMatrix11, newOrder);

	temp4 = subtract(secondMatrix12, secondMatrix22, newOrder);
	vector<vector<int>> m3 = this->multiply(firstMatrix11, temp4, newOrder);

	temp5 = subtract(secondMatrix21, secondMatrix11, newOrder);
	vector<vector<int>> m4 = this->multiply(firstMatrix22, temp5, newOrder);

	temp6 = add(firstMatrix11, firstMatrix12, newOrder);
	vector<vector<int>> m5 = this->multiply(temp6, secondMatrix22, newOrder);

	temp7 = subtract(firstMatrix21, firstMatrix11, newOrder);
	temp8 = add(secondMatrix11, secondMatrix12, newOrder);
	vector<vector<int>> m6 = this->multiply(temp7, temp8, newOrder);

	temp9 = subtract(firstMatrix12, firstMatrix22, newOrder);
	temp10 = add(secondMatrix21, secondMatrix22, newOrder);
	vector<vector<int>> m7 = this->multiply(temp9, temp10, newOrder);*/

	/*deleteMatrix(firstMatrix11, newOrder);
	deleteMatrix(firstMatrix12, newOrder);
	deleteMatrix(firstMatrix21, newOrder);
	deleteMatrix(firstMatrix22, newOrder);

	deleteMatrix(secondMatrix11, newOrder);
	deleteMatrix(secondMatrix12, newOrder);
	deleteMatrix(secondMatrix21, newOrder);
	deleteMatrix(secondMatrix22, newOrder);*/

	/*deleteMatrix(temp1, newOrder);
	deleteMatrix(temp2, newOrder);
	deleteMatrix(temp3, newOrder);
	deleteMatrix(temp4, newOrder);
	deleteMatrix(temp5, newOrder);
	deleteMatrix(temp6, newOrder);
	deleteMatrix(temp7, newOrder);
	deleteMatrix(temp8, newOrder);
	deleteMatrix(temp9, newOrder);
	deleteMatrix(temp10, newOrder);*/

	// Result matrix

	vector<vector<int>> c11 = add(subtract(add(m1, m4, newOrder), m5, newOrder), m7, newOrder);
	vector<vector<int>> c12 = add(m3, m5, newOrder);
	vector<vector<int>> c21 = add(m2, m4, newOrder);
	vector<vector<int>> c22 = add(add(subtract(m1, m2, newOrder), m3, newOrder), m6, newOrder);

	/*int **temp3 = createEmptyMatrix(newOrder);

	temp3 = add(m1, m4, newOrder, temp3);
	temp3 = subtract(temp3, m5, newOrder, temp3);	
	int **c11 = add(temp3, m7, newOrder);

	int **c12 = add(m3, m5, newOrder);
	int **c21 = add(m2, m4, newOrder);

	temp3 = subtract(m1, m2, newOrder, temp3);
	temp3 = add(temp3, m3, newOrder, temp3);
	int **c22 = add(temp3, m6, newOrder);*/

	/*deleteMatrix(m1, newOrder);
	deleteMatrix(m2, newOrder);
	deleteMatrix(m3, newOrder);
	deleteMatrix(m4, newOrder);
	deleteMatrix(m5, newOrder);
	deleteMatrix(m6, newOrder);
	deleteMatrix(m7, newOrder);*/

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

	/*deleteMatrix(c11, newOrder);
	deleteMatrix(c12, newOrder);
	deleteMatrix(c21, newOrder);
	deleteMatrix(c22, newOrder);

	deleteMatrix(m1, newOrder);
	deleteMatrix(m2, newOrder);
	deleteMatrix(m3, newOrder);
	deleteMatrix(m4, newOrder);
	deleteMatrix(m5, newOrder);
	deleteMatrix(m6, newOrder);
	deleteMatrix(m7, newOrder);*/

	/*deleteMatrix(firstMatrix11, newOrder);
	deleteMatrix(firstMatrix12, newOrder);
	deleteMatrix(firstMatrix21, newOrder);
	deleteMatrix(firstMatrix22, newOrder);

	deleteMatrix(secondMatrix11, newOrder);
	deleteMatrix(secondMatrix12, newOrder);
	deleteMatrix(secondMatrix21, newOrder);
	deleteMatrix(secondMatrix22, newOrder);*/

	return resultMatrix;
};