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
		
		char main[param[0].size() + 1];
		strcpy(main, param[0].c_str());

		int funcID = cmdCheck(main);
		switch(funcID){
			case 0: //SAVE
				saveFunction();
				break;
			case 1: //LOAD
				loadFunction(param);
				break;
			case 2: //DOWNLOAD
				downloadFunction(param);
				break;
			case 3: //CREATE
				createFunction(param);
				break;
			case 4: //RM
				rmFunction(param);
				break;
			case 5: //DETAILS
				detailsFunction(param);
				break;
			case 6: //OPEN
				openFunction(param);
				break;
			case 7: //LS
				lsFunction();
				break;
			case 8: //INFO
				infoFunction(); 
				break;
			case -1:
				// NOT FOUND
				break;
			case -2: //EXIT
				return 0;
			case -3: //CLEAR
				break;
			default:
				cout << "\nAlan o Guille, something happened, this is an error in the Console \n" << endl;
				break;
		}

		
	}
	return 0;
}
