#ifndef STRASSEN_INDEX_ALGORITHM_H
#define STRASSEN_INDEX_ALGORITHM_H

#include "MatrixMultiplication.h"
#include "NaiveAlgorithm.h"
#include <vector>

using namespace std;

class StrassenIndexAlgorithm : public MatrixMultiplication
{
	public:
		StrassenIndexAlgorithm()
		{
			this->naiveMultiplication = new NaiveAlgorithm();
		}
		~StrassenIndexAlgorithm()
		{
			delete this->naiveMultiplication;
		}
		vector<vector<int>> multiply(vector<vector<int>>& matrixA, vector<vector<int>>& matrixB, int order);
		vector<vector<int>> multiply(vector<vector<int>>& matrixA, int ai, int aj, vector<vector<int>>& matrixB, int bi, short bj, int order);

	private:
		MatrixMultiplication *naiveMultiplication;		
};

#endif