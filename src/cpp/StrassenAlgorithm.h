#ifndef STRASSEN_ALGORITHM_H
#define STRASSEN_ALGORITHM_H

#include "MatrixMultiplication.h"
#include "BasicAlgorithm.h"

using namespace std;

class StrassenAlgorithm : public MatrixMultiplication
{
	public:
		StrassenAlgorithm()
		{
			this->basicMultiplication = new BasicAlgorithm();
		}
		~StrassenAlgorithm()
		{
			delete this->basicMultiplication;
		}
		short **multiply(short **firstMatrix, short **secondMatrix, int order);

	private:
		MatrixMultiplication *basicMultiplication;
};

#endif