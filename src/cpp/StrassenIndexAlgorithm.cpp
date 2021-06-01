#include "StrassenIndexAlgorithm.h"

#include <iostream>
#include <omp.h>
#include <math.h>
#include "MatrixBuilder.h"
#include "MatrixOperations.h"

using namespace std;


vector<vector<int>> StrassenIndexAlgorithm::multiply(vector<vector<int>> &matrixA, vector<vector<int>> &matrixB, int order)
{
	return multiply(matrixA, 0, 0, matrixB, 0, 0, order);
}

vector<vector<int>> StrassenIndexAlgorithm::multiply(vector<vector<int>> &matrixA, int ai, int aj, vector<vector<int>> &matrixB, int bi, short bj, int order)
{
	if (order <= 128)
	{
		return this->naiveMultiplication->multiply(matrixA, matrixB, order);
		vector<vector<int>> resultMatrix(order, vector<int>(order));
		resultMatrix[0][0] = matrixA[ai][aj] * matrixB[bi][bj];
		return resultMatrix;
	}

	int newOrder = order / 2;

	// Creates partitions for input matrices

	//a11 matrixA, ai, aj,
	//a12 matrixA, ai, aj + newOrder,
	//a21 matrixA, ai + newOrder, aj,
	//a22 matrixA, ai + newOrder, aj + newOrder,
	//b11 matrixB, bi, bj,
	//b12 matrixB, bi, bj + newOrder,
	//b21 matrixB, bi + newOrder, bj,
	//b22 matrixB, bi + newOrder, bj + newOrder,

	// b12 - b22
	vector<vector<int>> s1(newOrder, vector<int>(newOrder));
	s1 = subtract(matrixB, bi, bj + newOrder, matrixB, bi + newOrder, bj + newOrder, newOrder);
	// a11 + a12
	vector<vector<int>> s2(newOrder, vector<int>(newOrder));
	s2 = add(matrixA, ai, aj, matrixA, ai, aj + newOrder, newOrder);
	//  a21 + a22
	vector<vector<int>> s3(newOrder, vector<int>(newOrder));
	s3 = add(matrixA, ai + newOrder, aj, matrixA, ai + newOrder, aj + newOrder, newOrder);
	// b21 - b11
	vector<vector<int>> s4(newOrder, vector<int>(newOrder));
	s4 = subtract(matrixB, bi + newOrder, bj, matrixB, bi, bj, newOrder);
	// a11 + a22
	vector<vector<int>> s5(newOrder, vector<int>(newOrder));
	s5 = add(matrixA, ai, aj, matrixA, ai + newOrder, aj + newOrder, newOrder);
	// b11 + b22
	vector<vector<int>> s6(newOrder, vector<int>(newOrder));
	s6 = add(matrixB, bi, bj, matrixB, bi + newOrder, bj + newOrder, newOrder);
	// a12 - a22
	vector<vector<int>> s7(newOrder, vector<int>(newOrder));
	s7 = subtract(matrixA, ai, aj + newOrder, matrixA, ai + newOrder, aj + newOrder, newOrder);
	// b21 + b22
	vector<vector<int>> s8(newOrder, vector<int>(newOrder));
	s8 = add(matrixB, bi + newOrder, bj, matrixB, bi + newOrder, bj + newOrder, newOrder);
	// a11 - a21
	vector<vector<int>> s9(newOrder, vector<int>(newOrder));
	s9 = subtract(matrixA, ai, aj, matrixA, ai + newOrder, aj, newOrder);
	// b11 + b12
	vector<vector<int>> s10(newOrder, vector<int>(newOrder));
	s10 = add(matrixB, bi, bj, matrixB, bi, bj + newOrder, newOrder);

	//a11[i][j] = matrixA[i][j];
	//a12[i][j] = matrixA[i][newOrder + j];
	//a21[i][j] = matrixA[newOrder + i][j];
	//a22[i][j] = matrixA[newOrder + i][newOrder + j];
	//b11[i][j] = matrixB[i][j];
	//b12[i][j] = matrixB[i][newOrder + j];
	//b21[i][j] = matrixB[newOrder + i][j];
	//b22[i][j] = matrixB[newOrder + i][newOrder + j];

	// p1 = a11*s1 = a11*b12 - a11*b22
	vector<vector<int>> p1 = this->multiply(matrixA, ai, aj, s1, 0, 0, newOrder);

	// p2 = s2*b22 = a11*b22 + a12*b22
	vector<vector<int>> p2 = this->multiply(s2, 0, 0, matrixB, bi + newOrder, bj + newOrder, newOrder);

	// p3 = s3*b11 = a21*b11 + a22*b11
	vector<vector<int>> p3 = this->multiply(s3, 0, 0, matrixB, bi, bj, newOrder);

	// p4 = a22*s4 = a22*b21 - a22*b11
	vector<vector<int>> p4 = this->multiply(matrixA, ai + newOrder, aj + newOrder, s4, 0, 0, newOrder);

	// p5 = s5*s6 = a11*b11 + a11*b22 + a22*b11 + a22*b22
	vector<vector<int>> p5 = this->multiply(s5, 0, 0, s6, 0, 0, newOrder);

	// p6 = s7*s8 = a12*b21 + a12*b22 - a22*b21 - a22*b22
	vector<vector<int>> p6 = this->multiply(s7, 0, 0, s8, 0, 0, newOrder);

	// p7 = s9*s10 = a11*b11 + a11*b12 - a21*b11 - a21*b12
	vector<vector<int>> p7 = this->multiply(s9, 0, 0, s10, 0, 0, newOrder);

	// Result matrix calculation (loops merged)

	vector<vector<int>> resultMatrix(order, vector<int>(order));

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
}