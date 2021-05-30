#include <iostream>
#include <chrono>
#include <math.h>
#include "InstanceDataLoader.h"
#include "InstanceData.h"
#include "MatrixMultiplication.h"
#include "BasicAlgorithm.h"
#include "MatrixBuilder.h"
#include "StrassenAlgorithm.h"

using namespace std;

int main(int argc, char **argv)
{
	// Load instance data
	
	InstanceDataLoader *instanceDataLoader = new InstanceDataLoader();
	InstanceData instanceData = instanceDataLoader->loadInstance(argv[1]);

	// Basic algorithm execution

	/*MatrixMultiplication *matrixMultiplication = new BasicAlgorithm();

	cout << endl;
	cout << "# Processing matrix multiplication (Basic algorithm)..." << endl;
	cout << endl;

	matrixMultiplication->execute(instanceData);
	delete matrixMultiplication;*/

	// Strassen algorithm execution

	MatrixMultiplication *matrixMultiplication = new StrassenAlgorithm();

	cout << endl;
	cout << "# Processing matrix multiplication (Strassen algorithm)..." << endl;
	cout << endl;

	matrixMultiplication->execute(instanceData);
	delete matrixMultiplication;
}