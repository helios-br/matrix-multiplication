#include "StrassenAlgorithm.h"

#include <iostream>
#include <omp.h>
#include <math.h>
#include "MatrixBuilder.h"
#include "MatrixOperations.h"

using namespace std;

vector<vector<int>> StrassenAlgorithm::multiply(vector<vector<int>> &matrixA, vector<vector<int>> &matrixB, int order)
{
	if (order <= 32)
	{
		return this->naiveMultiplication->multiply(matrixA, matrixB, order);
	}

	int newOrder = order / 2;

	// Creates partitions for input matrices

	//a11 matrixA, 0, 0
	//a12 matrixA, 0, newOrder
	//a21 matrixA, newOrder, 0
	//a22 matrixA, newOrder, newOrder
	//b11 matrixB, 0, 0
	//b12 matrixB, 0, newOrder
	//b21 matrixB, newOrder, 0
	//b22 matrixB, newOrder, newOrder

	vector<vector<int>> a11 (newOrder, vector<int>(newOrder));
	vector<vector<int>> a22 (newOrder, vector<int>(newOrder));
	vector<vector<int>> b22 (newOrder, vector<int>(newOrder));
	vector<vector<int>> b11 (newOrder, vector<int>(newOrder));

	// b12 - b22
	vector<vector<int>> s1 (newOrder, vector<int>(newOrder));
	// a11 + a12
	vector<vector<int>> s2 (newOrder, vector<int>(newOrder));
	//  a21 + a22
	vector<vector<int>> s3 (newOrder, vector<int>(newOrder));
	// b21 - b11
	vector<vector<int>> s4 (newOrder, vector<int>(newOrder));
	// a11 + a22
	vector<vector<int>> s5 (newOrder, vector<int>(newOrder));
	// b11 + b22
	vector<vector<int>> s6 (newOrder, vector<int>(newOrder));
	// a12 - a22
	vector<vector<int>> s7 (newOrder, vector<int>(newOrder));
	// b21 + b22
	vector<vector<int>> s8 (newOrder, vector<int>(newOrder));
	// a11 - a21
	vector<vector<int>> s9 (newOrder, vector<int>(newOrder));
	// b11 + b12
	vector<vector<int>> s10 (newOrder, vector<int>(newOrder));

	//a11[i][j] = matrixA[i][j];
	//a12[i][j] = matrixA[i][newOrder + j];
	//a21[i][j] = matrixA[newOrder + i][j];
	//a22[i][j] = matrixA[newOrder + i][newOrder + j];
	//b11[i][j] = matrixB[i][j];
	//b12[i][j] = matrixB[i][newOrder + j];
	//b21[i][j] = matrixB[newOrder + i][j];
	//b22[i][j] = matrixB[newOrder + i][newOrder + j];

	for (int i = 0; i < newOrder; i++) {
		for (int j = 0; j < newOrder; j++) {
			int newOrderPlusI = newOrder + i;
			int newOrderPlusJ = newOrder + j;

			a11[i][j] = matrixA[i][j];
			a22[i][j] = matrixA[newOrderPlusI][newOrderPlusJ];
			s2[i][j] = matrixA[i][j] + matrixA[i][newOrderPlusJ];
			s3[i][j] = matrixA[newOrderPlusI][j] + matrixA[newOrderPlusI][newOrderPlusJ];
			s5[i][j] = matrixA[i][j] + matrixA[newOrderPlusI][newOrderPlusJ];
			s7[i][j] = matrixA[i][newOrderPlusJ] - matrixA[newOrderPlusI][newOrderPlusJ];
			s9[i][j] = matrixA[i][j] - matrixA[newOrderPlusI][j];

			b11[i][j] = matrixB[i][j];
			b22[i][j] = matrixB[newOrderPlusI][newOrderPlusJ];
			s1[i][j] = matrixB[i][newOrderPlusJ] - matrixB[newOrderPlusI][newOrderPlusJ];
			s4[i][j] = matrixB[newOrderPlusI][j] - matrixB[i][j];
			s6[i][j] = matrixB[i][j] + matrixB[newOrderPlusI][newOrderPlusJ];
			s8[i][j] = matrixB[newOrderPlusI][j] + matrixB[newOrderPlusI][newOrderPlusJ];
			s10[i][j] = matrixB[i][j] + matrixB[i][newOrderPlusJ];
		}
	}

	// p1 = a11*s1 = a11*b12 - a11*b22
	vector<vector<int>> p1 = this->multiply(a11, s1, newOrder);

	// p2 = s2*b22 = a11*b22 + a12*b22
	vector<vector<int>> p2 = this->multiply(s2, b22, newOrder);

	// p3 = s3*b11 = a21*b11 + a22*b11
	vector<vector<int>> p3 = this->multiply(s3, b11, newOrder);

	// p4 = a22*s4 = a22*b21 - a22*b11
	vector<vector<int>> p4 = this->multiply(a22, s4, newOrder);

	// p5 = s5*s6 = a11*b11 + a11*b22 + a22*b11 + a22*b22
	vector<vector<int>> p5 = this->multiply(s5, s6, newOrder);

	// p6 = s7*s8 = a12*b21 + a12*b22 - a22*b21 - a22*b22
	vector<vector<int>> p6 = this->multiply(s7, s8, newOrder);

	// p7 = s9*s10 = a11*b11 + a11*b12 - a21*b11 - a21*b12
	vector<vector<int>> p7 = this->multiply(s9, s10, newOrder);

	// Result matrix calculation (loops merged)

	vector<vector<int>> resultMatrix (order, vector<int>(order));

	for (int i = 0; i < newOrder; i++) 
	{
		for (int j = 0; j < newOrder; j++) 
		{
			resultMatrix[i][j] = p5[i][j] + p4[i][j] - p2[i][j] + p6[i][j];
			resultMatrix[i][j + newOrder] = p1[i][j] + p2[i][j];
			resultMatrix[newOrder + i][j] = p3[i][j] + p4[i][j];
			resultMatrix[newOrder + i][newOrder + j] = p5[i][j] + p1[i][j] - p3[i][j] - p7[i][j];
		}
	}

	return resultMatrix;
};

vector<vector<int>> StrassenAlgorithm::multiply(vector<vector<int>> &matrixA, int ai, int aj, vector<vector<int>> &matrixB, int bi, short bj, int order)
{
	vector<vector<int>> resultMatrix;
	return resultMatrix;
}