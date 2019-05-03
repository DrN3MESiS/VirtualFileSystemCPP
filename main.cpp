#include <iostream>
#include <cstring>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include "functions.h"
#define version "\nVirtual File System [Version 0.1b]\nCreated by AEMN & GGM\n"

using namespace std;

int main()
{
	cout << version << endl;
	string command;
	while (true)
	{
		cout << "$$ > :";
		getline(cin, command);

		char tmp[command.size() + 1];
		strcpy(tmp, command.c_str());
		
		char *pch;
		pch = strtok(tmp, " ");
		
		int temp = checkForCommand(pch);

//		while (pch != NULL)
//		{
//			cout << pch << endl;
//			pch = strtok(NULL, " ");
//		}
	}
	return 0;
}
