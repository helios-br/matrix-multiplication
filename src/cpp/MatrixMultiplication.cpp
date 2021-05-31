#include "MatrixMultiplication.h"

#include <iostream>
#include <chrono>
#include <math.h>
#include "MatrixBuilder.h"
#include "InstanceData.h"
#include <chrono>
#include <iomanip>

using namespace std;

void MatrixMultiplication::execute(InstanceData instanceData)
{
	int initialK = 1;

	vector<int> orders;
	vector<float> times;

	for (int k = initialK, index = 0; k <= instanceData.kMax; k++, index++)
	{
		int matrixOrder = pow(2, k);
		float totalTimeForK = 0;

		cout << "\n##### New configuration. k = " << k << ", matrix order = " << matrixOrder << endl;

		for (int i = 0; i < instanceData.numberOfMatrixes; i++)
		{
			// Matrices creation

			//cout << endl;
			//cout << "# New matrices created" << endl;
			vector<vector<int>> matrix1 = createPopulatedMatrix(matrixOrder, instanceData.minElementValue, instanceData.maxElementValue);
			//printMatrix(matrix1, matrixOrder);
			vector<vector<int>> matrix2 = createPopulatedMatrix(matrixOrder, instanceData.minElementValue, instanceData.maxElementValue);
			//printMatrix(matrix2, matrixOrder);

			// Algorithm execution

			auto startTime = std::chrono::high_resolution_clock::now();
			vector<vector<int>> resultMatrix = this->multiply(matrix1, matrix2, matrixOrder);
			//printMatrix(resultMatrix, matrixOrder);
			auto endTime = std::chrono::high_resolution_clock::now();
			auto duration = (std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count());
			float time = (float)duration / 1000000;
			totalTimeForK += time;
			//printMatrixElementsSum(resultMatrix, matrixOrder);
		}

		orders.push_back(matrixOrder);
		times.push_back(totalTimeForK / instanceData.numberOfMatrixes);
	}

	// Output results

	cout << endl;
	cout << "---- Processing time ----" << endl;
	cout << std::fixed << std::setprecision(10);

	for (unsigned index = 0; index < orders.size(); index++)
	{
		cout << endl;
		cout << "order = " << orders[index] << endl;
		cout << "time =  " << times[index] << " seconds" << endl;
	}

	cout << "Done!" << endl;
}