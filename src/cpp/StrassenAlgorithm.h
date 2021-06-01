#ifndef STRASSEN_ALGORITHM_H
#define STRASSEN_ALGORITHM_H

#include "MatrixMultiplication.h"
#include "NaiveAlgorithm.h"
#include <vector>

using namespace std;

class StrassenAlgorithm : public MatrixMultiplication
{
	public:
		StrassenAlgorithm()
		{
			this->naiveMultiplication = new NaiveAlgorithm();
		}
		~StrassenAlgorithm()
		{
			delete this->naiveMultiplication;
		}
		vector<vector<int>> multiply(vector<vector<int>>& firstMatrix, vector<vector<int>>& secondMatrix, int order);

	private:
		MatrixMultiplication *naiveMultiplication;
		vector<vector<int>> multiply(vector<vector<int>>& matrixA, int ai, int aj, vector<vector<int>>& matrixB, int bi, short bj, int order);
};

#endif