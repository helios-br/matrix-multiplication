#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

inline char *convertToChar(string text)
{
	char *charArray = new char(text.size());
	for (unsigned i = 0; i < text.size(); i++)
	{
		charArray[i] = text[i];
	}
	return charArray;
}

#endif