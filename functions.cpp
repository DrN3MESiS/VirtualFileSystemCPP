#include "functions.h"
#include <iostream>
#define save 431
#define load 416
#define download 856
#define create 728
#define rm 637
#define details 742

using namespace std;

int toInt(char str[]){
	int value = 0;
	for(int i = 0; i < sizeof(str); i++){
		char t = str[i];
		value += (int)t;
	}
	return value;
}

int checkForCommand(char str[]){
	int index = toInt(str);
	switch(index){
		case save:
			cout << "Called SAVE" << endl;
			return 0;
			break;
		
		case load:
			cout << "Called LOAD" << endl;
			return 1;
			
		case download:
			cout << "Called DOWNLOAD" << endl;
			return 2;
			
		default:
			cout << "command not found" << endl;
			return -1;
	}
}
