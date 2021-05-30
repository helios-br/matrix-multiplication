#include <iostream>
#include <chrono>
#include <math.h>
#include <iomanip>
#include "InstanceDataLoader.h"
#include "InstanceData.h"
#include "MatrixMultiplication.h"
#include "BasicAlgorithm.h"
#include "MatrixBuilder.h"
#include "StrassenAlgorithm.h"
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
	// Load instance data

	InstanceDataLoader *instanceDataLoader = new InstanceDataLoader();
	InstanceData instanceData = instanceDataLoader->loadInstance(argv[1]);
	delete instanceDataLoader;

	// Basic algorithm execution

	/*MatrixMultiplication *basicMultiplication = new BasicAlgorithm();

	cout << endl;
	cout << "# Processing matrix multiplication (Basic algorithm)..." << endl;
	cout << endl;

	basicMultiplication->execute(instanceData);
	delete basicMultiplication;*/

	// Strassen algorithm execution

	/*MatrixMultiplication *strassenMultiplication = new StrassenAlgorithm();

	cout << endl;
	cout << "# Processing matrix multiplication (Strassen algorithm)..." << endl;
	cout << endl;

	strassenMultiplication->execute(instanceData);
	delete strassenMultiplication;*/

	// Execution

	int initialK = 1;
	int totalProcessingKs = instanceData.kMax - initialK + 1;
	
	float basicAlgorithmTime[totalProcessingKs];
	float strassenAlgorithmTime[totalProcessingKs];	

	// Basic execution 

	//cout << endl;
	//cout << "@@@@@@ BASIC EXECUTION" << endl;
	
	MatrixMultiplication *basicMultiplication = new BasicAlgorithm();	
	MatrixMultiplication *strassenMultiplication = new StrassenAlgorithm();

	for (int k = initialK, index = 0; k <= instanceData.kMax; k++, index++)
	{		
		int matrixOrder = pow(2, k);
		float totalBasicAlgorithmTimeForK = 0;
		float totalStrassenAlgorithmTimeForK = 0;

		cout << "\n##### New configuration. k = " << k << ", matrix order = " << matrixOrder << endl;

		for (int i = 0; i < instanceData.numberOfMatrixes; i++)
		{
			cout << endl;
			cout << "# New matrices created" << endl;
			vector<vector<int>> matrix1 = createPopulatedMatrix(matrixOrder, instanceData.minElementValue, instanceData.maxElementValue);
			//printMatrix(matrix1, matrixOrder);
			vector<vector<int>> matrix2 = createPopulatedMatrix(matrixOrder, instanceData.minElementValue, instanceData.maxElementValue);
			//printMatrix(matrix2, matrixOrder);

			// Basic algorithm

			auto startTime = std::chrono::high_resolution_clock::now();
			vector<vector<int>> resultMatrix = basicMultiplication->multiply(matrix1, matrix2, matrixOrder);
			auto endTime = std::chrono::high_resolution_clock::now();
			auto duration = (std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count());
			float time = (float)duration / 1000000;
			totalBasicAlgorithmTimeForK += time;
			printMatrixElementsSum(resultMatrix, matrixOrder);

			// Strassen algorithm

			auto startStrassenTime = std::chrono::high_resolution_clock::now();
			vector<vector<int>> resultStrassenMatrix = strassenMultiplication->multiply(matrix1, matrix2, matrixOrder);
			auto endStrassenTime = std::chrono::high_resolution_clock::now();
			auto strassenDuration = (std::chrono::duration_cast<std::chrono::microseconds>(endStrassenTime - startStrassenTime).count());
			float strassenTime = (float)strassenDuration / 1000000;
			totalStrassenAlgorithmTimeForK += strassenTime;
			printMatrixElementsSum(resultStrassenMatrix, matrixOrder);

			// Free memory

			deleteMatrix(matrix1, matrixOrder);
			deleteMatrix(matrix2, matrixOrder);
			deleteMatrix(resultMatrix, matrixOrder);
			deleteMatrix(resultStrassenMatrix, matrixOrder);
		}

		basicAlgorithmTime[index] = totalBasicAlgorithmTimeForK / totalProcessingKs;
		strassenAlgorithmTime[index] = totalStrassenAlgorithmTimeForK / totalProcessingKs;
	}

	delete basicMultiplication;
	delete strassenMultiplication;

	// Output results

	cout << endl;
	cout << "---- Processing time ----" << endl;
	cout << std::fixed << std::setprecision(10);

	for (int index = 0; index < totalProcessingKs; index++)
	{
		cout << endl;
		cout << "k = " << (index + initialK) << endl;
		cout << "Basic:    " << basicAlgorithmTime[index] << " seconds" << endl;
		cout << "Strassen: " << strassenAlgorithmTime[index] << " seconds" << endl;
	}

	cout << "Done!" << endl;	
}
