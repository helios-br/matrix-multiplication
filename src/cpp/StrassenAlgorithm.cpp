#include "StrassenAlgorithm.h"

#include <iostream>
#include <omp.h>
#include "MatrixBuilder.h"
#include "BasicAlgorithm.h"
#include "MatrixOperations.h"

using namespace std;

short **StrassenAlgorithm::multiply(short **firstMatrix, short **secondMatrix, int order)
{
	if (order == 1)
	{
		return this->basicMultiplication->multiply(firstMatrix, secondMatrix, order);
	}

	short newOrder = order / 2;

	// Creates partitions

	short **firstMatrix11 = createEmptyMatrix(newOrder);
	short **firstMatrix12 = createEmptyMatrix(newOrder);
	short **firstMatrix21 = createEmptyMatrix(newOrder);
	short **firstMatrix22 = createEmptyMatrix(newOrder);

	short **secondMatrix11 = createEmptyMatrix(newOrder);
	short **secondMatrix12 = createEmptyMatrix(newOrder);
	short **secondMatrix21 = createEmptyMatrix(newOrder);
	short **secondMatrix22 = createEmptyMatrix(newOrder);

	for (short i = 0; i < newOrder; i++)
	{
		for (short j = 0; j < newOrder; j++)
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

	short **m1 = this->multiply(add(firstMatrix11, firstMatrix22, newOrder), add(secondMatrix11, secondMatrix22, newOrder), newOrder);
	short **m2 = this->multiply(add(firstMatrix21, firstMatrix22, newOrder), secondMatrix11, newOrder);
	short **m3 = this->multiply(firstMatrix11, subtract(secondMatrix12, secondMatrix22, newOrder), newOrder);
	short **m4 = this->multiply(firstMatrix22, subtract(secondMatrix21, secondMatrix11, newOrder), newOrder);
	short **m5 = this->multiply(add(firstMatrix11, firstMatrix12, newOrder), secondMatrix22, newOrder);
	short **m6 = this->multiply(subtract(firstMatrix21, firstMatrix11, newOrder), add(secondMatrix11, secondMatrix12, newOrder), newOrder);
	short **m7 = this->multiply(subtract(firstMatrix12, firstMatrix22, newOrder), add(secondMatrix21, secondMatrix22, newOrder), newOrder);

	// Result matrix

	short **c11 = add(subtract(add(m1, m4, newOrder), m5, newOrder), m7, newOrder);
	short **c12 = add(m3, m5, newOrder); // ERRO
	short **c21 = add(m2, m4, newOrder); 
	short **c22 = add(add(subtract(m1, m2, newOrder), m3, newOrder), m6, newOrder);

	short **resultMatrix = createEmptyMatrix(order);

	for (short i = 0; i < newOrder; i++)
	{
		for (short j = 0; j < newOrder; j++)
		{
			resultMatrix[i][j] = c11[i][j];
			resultMatrix[i][j + newOrder] = c12[i][j];
			resultMatrix[newOrder + i][j] = c21[i][j];
			resultMatrix[newOrder + i][newOrder + j] = c22[i][j];
		}
	}

	return resultMatrix;
};