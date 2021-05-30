#ifndef STRASSEN_ALGORITHM_H
#define STRASSEN_ALGORITHM_H

#include "MatrixMultiplication.h"
#include "BasicAlgorithm.h"
#include <vector>

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
		vector<vector<int>> multiply(vector<vector<int>> firstMatrix, vector<vector<int>> secondMatrix, int order);

	private:
		MatrixMultiplication *basicMultiplication;
};

#endif