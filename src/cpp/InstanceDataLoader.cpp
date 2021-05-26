#include "InstanceDataLoader.h"

#include <iostream>
#include <fstream>
#include <string>
#include "InstanceData.h"

using namespace std;

InstanceData InstanceDataLoader::loadInstance(char *instanceName)
{
	InstanceData instanceData;

	ifstream instanceStream(instanceName, ios::in);
	instanceStream >> instanceData.kMax;
	instanceStream >> instanceData.numberOfMatrixes;
	instanceStream >> instanceData.minElementValue >> instanceData.maxElementValue;
	
	return instanceData;
}