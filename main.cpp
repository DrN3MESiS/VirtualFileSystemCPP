#include <iostream>
#include <cstring>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "functions.h"
#define version "\nVirtual File System [Version 0.1b]\nCreated by AEMN & GGM\n"
#define vol_max_size 1073741824

using namespace std;

int main()
{
	cout << version << endl;
	while (true)
	{
		vector<string> param;
		string command;
		cout << "$$ > :";
		getline(cin, command);
		
		if(command.empty()){
			continue;
		}

		char tmp[command.size() + 1];
		strcpy(tmp, command.c_str());
		
		char *pch;
		pch = strtok(tmp, " ");
		while (pch != NULL)
		{
			param.push_back(pch);
			pch = strtok(NULL, " ");
		}
		
		char[] main= param[0];

		int funcID = cmdCheck(main);
		switch(funcID){
			default:
				break;
		}

		
	}
	return 0;
}
