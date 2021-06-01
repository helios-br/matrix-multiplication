#include <iostream>
#include "InstanceDataLoader.h"
#include "InstanceData.h"
#include "MatrixMultiplication.h"
#include "NaiveAlgorithm.h"
#include "StrassenAlgorithm.h"
#include "AlgorithmsAnalysis.h"

using namespace std;

int main(int argc, char **argv)
{
	// Load instance data

	InstanceDataLoader *instanceDataLoader = new InstanceDataLoader();
	InstanceData instanceData = instanceDataLoader->loadInstance(argv[1]);
	delete instanceDataLoader;

	// Naive algorithm execution only

	/* MatrixMultiplication *naiveMultiplication = new NaiveAlgorithm();
	naiveMultiplication->execute(instanceData);
	delete naiveMultiplication; */

	// Strassen algorithm execution only

	/* MatrixMultiplication *strassenMultiplication = new StrassenAlgorithm();
	strassenMultiplication->execute(instanceData);
	delete strassenMultiplication; */

	// Algorithms analysis

	executeAnalysis(instanceData);
}
