#include "MatrixMultiplication.h"

#include <iostream>
#include <chrono>
#include <math.h>
#include "MatrixBuilder.h"
#include "InstanceData.h"

using namespace std;

void MatrixMultiplication::execute(InstanceData instanceData)
{
	auto startTime = std::chrono::high_resolution_clock::now();

	for (int k = 1; k <= instanceData.kMax; k++)
	{
		int matrixOrder = pow(2, k);

		for (int i = 0; i < instanceData.numberOfMatrixes; i++)
		{
			fprintf(stderr, "\n@ New multiplication\n");

			vector<vector<int>> matrix1 = createPopulatedMatrix(matrixOrder, instanceData.minElementValue, instanceData.maxElementValue);
			vector<vector<int>> matrix2 = createPopulatedMatrix(matrixOrder, instanceData.minElementValue, instanceData.maxElementValue);
			vector<vector<int>> resultMatrix = this->multiply(matrix1, matrix2, matrixOrder);

			// Output data
			
			printMatrix(matrix1, matrixOrder);
			printMatrix(matrix2, matrixOrder);
			printMatrix(resultMatrix, matrixOrder);
		}
	}

	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = (std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count());
	float time = (float)duration / 1000000;

	cout << "Algorithm time: " << time << " seconds " << endl;
	cout << "Done!" << endl;
}