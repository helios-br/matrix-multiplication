#ifndef INSTANCE_DATA_H
#define INSTANCE_DATA_H

#include <iostream>

using namespace std;

struct InstanceData
{
	int kMax;
	int numberOfMatrixes;
	int minElementValue;
	int maxElementValue;

	void print()
	{
		cout << endl;
		cout << "---- Instance data ----" << endl;
		cout << "k_max: " << kMax << endl;
		cout << "numberOfMatrixes: " << this->numberOfMatrixes << endl;
		cout << "range: " << this->minElementValue << " .. " << this->maxElementValue << endl;
	}
};

#endif