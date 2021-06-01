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

inline void waitForKey()
{
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) // every keypress registered, also arrow keys
	cout << endl;
	cout << "Press any key to continue..." << endl;

	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	_getch();
	#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
	cout << endl;
	cout << "Press ENTER to continue..." << endl;

	std::cin.clear();
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::cin.get();
#endif

	return;
}

#endif