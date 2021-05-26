#include "BasicAlgorithm.h"

#include <iostream>
#include "MatrixBuilder.h"

using namespace std;

void BasicAlgorithm::execute(short **firstMatrix, short **secondMatrix, int order) {
	
	short** resultMatrix = createEmptyMatrix(order);

	for (int i = 0; i < order; i++) {
		for (int j = 0; j < order; j++) {
			for (int k = 0; k < order; k++) {
				resultMatrix[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
			}
		}
	}

	deleteMatrix(resultMatrix, order);
};