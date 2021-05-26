#include <iostream>
#include "InstanceDataLoader.h"
#include "InstanceData.h"
#include "StringUtil.h"
#include "MatrixMultiplication.h"
#include "BasicAlgorithm.h"
#include "MatrixBuilder.h"
#include <chrono>
#include <math.h>

using namespace std;

string normalizeFileName(char *parameter)
{
	string fileName = parameter;
	size_t foundDot = fileName.find(".");
	if (foundDot != string::npos)
	{
		return fileName;
	}
	return fileName + ".in";
}

int main(int argc, char **argv)
{

	// Load instance data

	string fileName = normalizeFileName(argv[1]);
	cout << "fileName: " << fileName << endl;
	InstanceDataLoader *instanceDataLoader = new InstanceDataLoader();
	InstanceData instanceData = instanceDataLoader->loadInstance(convertToChar(fileName));
	instanceData.print();

	// Execute (basic algorithm)

	MatrixMultiplication *matrixMultiplication = new BasicAlgorithm();

	cout << endl;
	cout << "# Processing..." << endl;
	cout << endl;

	auto firstTime = std::chrono::high_resolution_clock::now();

	for (int k = 5; k <= instanceData.kMax; k++)
	{
		int matrixOrder = pow(2, k);

		for (int i = 0; i < instanceData.numberOfMatrixes; i++)
		{
			short **matrix1 = createPopulatedMatrix(matrixOrder, instanceData.minElementValue, instanceData.maxElementValue);
			short **matrix2 = createPopulatedMatrix(matrixOrder, instanceData.minElementValue, instanceData.maxElementValue);			
			matrixMultiplication->execute(matrix1, matrix2, matrixOrder);
			deleteMatrix(matrix1, matrixOrder);
			deleteMatrix(matrix2, matrixOrder);
		}
	}

	auto lastTime = std::chrono::high_resolution_clock::now();
	auto duration = (std::chrono::duration_cast<std::chrono::microseconds>(lastTime - firstTime).count());

	float time = (float)duration / 1000000;

	cout << endl;
	cout << "Done! time: " << time << " seconds " << endl;
}