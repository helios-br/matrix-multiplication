#include <iostream>
#include <chrono>
#include <math.h>
#include <iomanip>
#include "InstanceDataLoader.h"
#include "InstanceData.h"
#include "MatrixMultiplication.h"
#include "NaiveAlgorithm.h"
#include "MatrixBuilder.h"
#include "StrassenAlgorithm.h"
#include "Gnuplot.h"
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

	vector<int> kValues;
	vector<float> naiveAlgorithmTime;
	vector<float> strassenAlgorithmTime;

	MatrixMultiplication *naiveMultiplication = new NaiveAlgorithm();
	MatrixMultiplication *strassenMultiplication = new StrassenAlgorithm();

	for (int k = initialK, index = 0; k <= instanceData.kMax; k++, index++)
	{
		int matrixOrder = pow(2, k);
		float totalNaiveAlgorithmTimeForK = 0;
		float totalStrassenAlgorithmTimeForK = 0;

		cout << "\n##### New configuration. k = " << k << ", matrix order = " << matrixOrder << endl;

		for (int i = 0; i < instanceData.numberOfMatrixes; i++)
		{
			cout << endl;
			cout << "# New matrices created" << endl;
			vector<vector<int>> matrix1 = createPopulatedMatrix(matrixOrder, instanceData.minElementValue, instanceData.maxElementValue);
			printMatrix(matrix1, matrixOrder);
			vector<vector<int>> matrix2 = createPopulatedMatrix(matrixOrder, instanceData.minElementValue, instanceData.maxElementValue);
			printMatrix(matrix2, matrixOrder);

			// Naive algorithm

			auto startTime = std::chrono::high_resolution_clock::now();
			vector<vector<int>> resultMatrix = naiveMultiplication->multiply(matrix1, matrix2, matrixOrder);
			auto endTime = std::chrono::high_resolution_clock::now();
			auto duration = (std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count());
			float time = (float)duration / 1000000;
			totalNaiveAlgorithmTimeForK += time;
			//printMatrixElementsSum(resultMatrix, matrixOrder);

			// Strassen algorithm

			auto startStrassenTime = std::chrono::high_resolution_clock::now();
			vector<vector<int>> resultStrassenMatrix = strassenMultiplication->multiply(matrix1, matrix2, matrixOrder);
			auto endStrassenTime = std::chrono::high_resolution_clock::now();
			auto strassenDuration = (std::chrono::duration_cast<std::chrono::microseconds>(endStrassenTime - startStrassenTime).count());
			float strassenTime = (float)strassenDuration / 1000000;
			totalStrassenAlgorithmTimeForK += strassenTime;
			//printMatrixElementsSum(resultStrassenMatrix, matrixOrder);
		}

		kValues.push_back(k);
		naiveAlgorithmTime.push_back(totalNaiveAlgorithmTimeForK / instanceData.numberOfMatrixes);
		strassenAlgorithmTime.push_back(totalStrassenAlgorithmTimeForK / instanceData.numberOfMatrixes);
	}

	delete naiveMultiplication;
	delete strassenMultiplication;

	// Output results

	cout << endl;
	cout << "---- Processing time ----" << endl;
	cout << std::fixed << std::setprecision(10);

	for (unsigned index = 0; index < kValues.size(); index++)
	{
		cout << endl;
		cout << "k = " << kValues[index] << endl;
		cout << "Naive:    " << naiveAlgorithmTime[index] << " seconds" << endl;
		cout << "Strassen: " << strassenAlgorithmTime[index] << " seconds" << endl;
	}

	cout << "Done!" << endl;

	// Gnuplot

	Gnuplot g1("teste2");
	g1.set_grid();
	g1.set_xlabel("K value");
	g1.set_ylabel("Time (seconds)");	
	g1.set_yautoscale();
	g1.set_xautoscale();
	//g1.set_yrange(0, strassenAlgorithmTime[strassenAlgorithmTime.size() - 1]);
	//g1.set_xrange(0, 10);
	g1.set_style("").plot_xy(kValues, naiveAlgorithmTime, "naive");
	g1.set_style("lines").plot_xy(kValues, naiveAlgorithmTime, "naive");
	g1.set_style("").plot_xy(kValues, strassenAlgorithmTime, "strassen");
	g1.set_style("lines").plot_xy(kValues, strassenAlgorithmTime, "strassen");

	waitForKey();
}


