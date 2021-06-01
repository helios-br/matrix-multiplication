#include "AlgorithmsAnalysis.h"

#include <iostream>
#include <chrono>
#include <math.h>
#include <iomanip>
#include "MatrixMultiplication.h"
#include "NaiveAlgorithm.h"
#include "MatrixBuilder.h"
#include "StrassenAlgorithm.h"
#include "StrassenIndexAlgorithm.h"
#include "Gnuplot.h"
#include <vector>
#include "StringUtil.h"

void executeAnalysis(InstanceData instanceData)
{
	// Execution

	int initialK = 5;

	vector<int> orders;
	vector<float> naiveAlgorithmTime;
	vector<float> strassenAlgorithmTime;
	vector<float> strassenIndexAlgorithmTime;

	MatrixMultiplication *naiveMultiplication = new NaiveAlgorithm();
	MatrixMultiplication *strassenMultiplication = new StrassenAlgorithm();
	MatrixMultiplication *strassenIndexMultiplication = new StrassenIndexAlgorithm();

	for (int k = initialK, index = 0; k <= instanceData.kMax; k++, index++)
	{
		int matrixOrder = pow(2, k);
		float totalNaiveAlgorithmTimeForK = 0;
		float totalStrassenAlgorithmTimeForK = 0;
		float totalStrassenIndexAlgorithmTimeForK = 0;

		cout << "\n##### New configuration. k = " << k << ", matrix order = " << matrixOrder << endl;

		for (int i = 0; i < instanceData.numberOfMatrixes; i++)
		{
			//cout << endl;
			//cout << "# New matrices created" << endl;
			vector<vector<int>> matrix1 = createPopulatedMatrix(matrixOrder, instanceData.minElementValue, instanceData.maxElementValue);
			//printMatrix(matrix1, matrixOrder);
			vector<vector<int>> matrix2 = createPopulatedMatrix(matrixOrder, instanceData.minElementValue, instanceData.maxElementValue);
			//printMatrix(matrix2, matrixOrder);

			// Naive algorithm

			auto startTime = std::chrono::high_resolution_clock::now();
			vector<vector<int>> resultMatrix = naiveMultiplication->multiply(matrix1, matrix2, matrixOrder);
			auto endTime = std::chrono::high_resolution_clock::now();
			auto duration = (std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count());
			float time = (float)duration / 1000000;
			totalNaiveAlgorithmTimeForK += time;
			cout << "Naive algorithm [" << i << "]: " << time << " seconds" << endl;
			//printMatrixElementsSum(resultMatrix, matrixOrder);
			//printMatrix(resultMatrix, matrixOrder);

			// Strassen algorithm

			auto startStrassenTime = std::chrono::high_resolution_clock::now();
			vector<vector<int>> resultStrassenMatrix = strassenMultiplication->multiply(matrix1, matrix2, matrixOrder);
			auto endStrassenTime = std::chrono::high_resolution_clock::now();
			auto strassenDuration = (std::chrono::duration_cast<std::chrono::microseconds>(endStrassenTime - startStrassenTime).count());
			float strassenTime = (float)strassenDuration / 1000000;
			totalStrassenAlgorithmTimeForK += strassenTime;
			cout << "Strassen algorithm [" << i << "]: " << strassenTime << " seconds" << endl;
			//printMatrixElementsSum(resultStrassenMatrix, matrixOrder);
			//printMatrix(resultStrassenMatrix, matrixOrder);

			// Strassen algorithm with index calculations

			auto startStrassenIndexTime = std::chrono::high_resolution_clock::now();
			vector<vector<int>> resultStrassenIndexMatrix = strassenIndexMultiplication->multiply(matrix1, matrix2, matrixOrder);
			auto endStrassenIndexTime = std::chrono::high_resolution_clock::now();
			auto strassenIndexDuration = (std::chrono::duration_cast<std::chrono::microseconds>(endStrassenIndexTime - startStrassenIndexTime).count());
			float strassenIndexTime = (float)strassenIndexDuration / 1000000;
			totalStrassenIndexAlgorithmTimeForK += strassenIndexTime;
			cout << "Strassen algorithm (index calculation) (" << i << "): " << strassenIndexTime << " seconds" << endl;
			//printMatrixElementsSum(resultStrassenIndexMatrix, matrixOrder);
			//printMatrix(resultStrassenIndexMatrix, matrixOrder);
		}

		orders.push_back(matrixOrder);
		naiveAlgorithmTime.push_back(totalNaiveAlgorithmTimeForK / instanceData.numberOfMatrixes);
		strassenAlgorithmTime.push_back(totalStrassenAlgorithmTimeForK / instanceData.numberOfMatrixes);
		strassenIndexAlgorithmTime.push_back(totalStrassenIndexAlgorithmTimeForK / instanceData.numberOfMatrixes);
	}

	delete naiveMultiplication;
	delete strassenMultiplication;
	delete strassenIndexMultiplication;

	// Output results

	cout << endl;
	cout << "---- Processing time ----" << endl;
	cout << std::fixed << std::setprecision(10);

	for (unsigned index = 0; index < orders.size(); index++)
	{
		cout << endl;
		cout << "order = " << orders[index] << endl;
		cout << "Naive:    " << naiveAlgorithmTime[index] << " seconds" << endl;
		cout << "Strassen: " << strassenAlgorithmTime[index] << " seconds" << endl;
		cout << "Strassen (index calculations): " << strassenIndexAlgorithmTime[index] << " seconds" << endl;
	}

	cout << "Done!" << endl;

	// Gnuplot

	Gnuplot g1("Results");
	g1.set_grid();
	g1.set_xlabel("Matrix order");
	g1.set_ylabel("Time (seconds)");
	g1.set_yautoscale();
	g1.set_xautoscale();
	g1.set_style("").plot_xy(orders, naiveAlgorithmTime, "naive");
	g1.set_style("lines").plot_xy(orders, naiveAlgorithmTime, "naive");
	g1.set_style("").plot_xy(orders, strassenAlgorithmTime, "strassen");
	g1.set_style("lines").plot_xy(orders, strassenAlgorithmTime, "strassen");
	g1.set_style("").plot_xy(orders, strassenIndexAlgorithmTime, "strassen index");
	g1.set_style("lines").plot_xy(orders, strassenIndexAlgorithmTime, "strassen index");

	waitForKey();
}