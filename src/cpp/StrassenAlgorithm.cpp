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

/*vector<vector<int>> StrassenAlgorithm::multiply(vector<vector<int>> firstMatrix, vector<vector<int>> secondMatrix, int order)
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

	vector<vector<int>> temp1 = createEmptyMatrix(newOrder);
	vector<vector<int>> temp2 = createEmptyMatrix(newOrder);

	add(firstMatrix11, firstMatrix22, newOrder, temp1);
	add(secondMatrix11, secondMatrix22, newOrder, temp2);
	vector<vector<int>>  m1 = this->multiply(temp1, temp2, newOrder);

	add(firstMatrix21, firstMatrix22, newOrder, temp1);
	vector<vector<int>> m2 = this->multiply(temp1, secondMatrix11, newOrder);

	subtract(secondMatrix12, secondMatrix22, newOrder, temp1);
	vector<vector<int>> m3 = this->multiply(firstMatrix11, temp1, newOrder);

	subtract(secondMatrix21, secondMatrix11, newOrder, temp1);
	vector<vector<int>> m4 = this->multiply(firstMatrix22, temp1, newOrder);

	add(firstMatrix11, firstMatrix12, newOrder, temp1);
	vector<vector<int>> m5 = this->multiply(temp1, secondMatrix22, newOrder);

	subtract(firstMatrix21, firstMatrix11, newOrder, temp1);
	add(secondMatrix11, secondMatrix12, newOrder, temp2);
	vector<vector<int>> m6 = this->multiply(temp1, temp2, newOrder);

	subtract(firstMatrix12, firstMatrix22, newOrder, temp1);
	add(secondMatrix21, secondMatrix22, newOrder, temp2);
	vector<vector<int>> m7 = this->multiply(temp1, temp2, newOrder);

	// Result matrix

	add(m1, m4, newOrder, temp1);
	subtract(temp1, m5, newOrder, temp2);	
	vector<vector<int>> c11 = add(temp2, m7, newOrder);

	vector<vector<int>> c12 = add(m3, m5, newOrder);
	vector<vector<int>> c21 = add(m2, m4, newOrder);

	subtract(m1, m2, newOrder, temp1);
	add(temp1, m3, newOrder, temp2);
	vector<vector<int>> c22 = add(temp2, m6, newOrder);

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
};*/

/*vector<vector<int>> StrassenAlgorithm::multiply(vector<vector<int>> firstMatrix, vector<vector<int>> secondMatrix, int order)
{
	if (order == 1)
	{
		return this->naiveMultiplication->multiply(firstMatrix, secondMatrix, order);
	}

	int newOrder = order / 2;

	// Creates partitions for input matrices

	vector<vector<int>> a11(newOrder, vector<int>(newOrder));
	vector<vector<int>> a12(newOrder, vector<int>(newOrder));
	vector<vector<int>> a21(newOrder, vector<int>(newOrder));
	vector<vector<int>> a22(newOrder, vector<int>(newOrder));

	vector<vector<int>> b11(newOrder, vector<int>(newOrder));
	vector<vector<int>> b12(newOrder, vector<int>(newOrder));
	vector<vector<int>> b21(newOrder, vector<int>(newOrder));
	vector<vector<int>> b22(newOrder, vector<int>(newOrder));

	for (int i = 0; i < newOrder; i++)
	{
		for (int j = 0; j < newOrder; j++)
		{
			a11[i][j] = firstMatrix[i][j];
			a12[i][j] = firstMatrix[i][newOrder + j];
			a21[i][j] = firstMatrix[newOrder + i][j];
			a22[i][j] = firstMatrix[newOrder + i][newOrder + j];
			b11[i][j] = secondMatrix[i][j];
			b12[i][j] = secondMatrix[i][newOrder + j];
			b21[i][j] = secondMatrix[newOrder + i][j];
			b22[i][j] = secondMatrix[newOrder + i][newOrder + j];
		}
	}

	// Cormen

	vector<vector<int>> s1 = subtract(b12, b22, newOrder);
	vector<vector<int>> s2 = add(a11, a12, newOrder);
	vector<vector<int>> s3 = add(a21, a22, newOrder);
	vector<vector<int>> s4 = subtract(b21, b11, newOrder);
	vector<vector<int>> s5 = add(a11, a22, newOrder);
	vector<vector<int>> s6 = add(b11, b22, newOrder);
	vector<vector<int>> s7 = subtract(a12, a22, newOrder);
	vector<vector<int>> s8 = add(b21, b22, newOrder);
	vector<vector<int>> s9 = subtract(a11, a21, newOrder);
	vector<vector<int>> s10 = add(b11, b12, newOrder);

	// Creates "P" matrices

	vector<vector<int>> p1 = this->multiply(a11, s1, newOrder);
	vector<vector<int>> p2 = this->multiply(s2, b22, newOrder);
	vector<vector<int>> p3 = this->multiply(s3, b11, newOrder);
	vector<vector<int>> p4 = this->multiply(a22, s4, newOrder);
	vector<vector<int>> p5 = this->multiply(s5, s6, newOrder);
	vector<vector<int>> p6 = this->multiply(s7, s8, newOrder);
	vector<vector<int>> p7 = this->multiply(s9, s10, newOrder);

	// Result matrix

	vector<vector<int>> c11 = add(subtract(add(p5, p4, newOrder), p2, newOrder), p6, newOrder);
	vector<vector<int>> c12 = add(p1, p2, newOrder);
	vector<vector<int>> c21 = add(p3, p4, newOrder);
	vector<vector<int>> c22 = subtract(add(subtract(p1, p3, newOrder), p5, newOrder), p7, newOrder);

	vector<vector<int>> resultMatrix(order, vector<int>(order));

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
};*/