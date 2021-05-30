#include "InstanceDataLoader.h"

#include <iostream>
#include <fstream>
#include <string>
#include "InstanceData.h"
#include "StringUtil.h"

using namespace std;

InstanceData InstanceDataLoader::loadInstance(char *instanceName)
{
	// Load file

	string fileName = normalizeFileName(instanceName);
	cout << "fileName: " << fileName << endl;
	ifstream instanceStream(convertToChar(fileName), ios::in);

	// Load data from file

	InstanceData instanceData;
	instanceStream >> instanceData.kMax;
	instanceStream >> instanceData.numberOfMatrixes;
	instanceStream >> instanceData.minElementValue >> instanceData.maxElementValue;

	instanceData.print();

	return instanceData;
}

string InstanceDataLoader::normalizeFileName(char *instanceName)
{
	string fileName = instanceName;
	size_t foundDot = fileName.find(".");
	if (foundDot != string::npos)
	{
		return fileName;
	}
	return fileName + ".in";
}