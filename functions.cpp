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

void checkForCommand(char str[]){
	int index = toInt(str);
	cout << index << endl;
	switch(index){
		case save:
			cout << "Called SAVE\n" << endl;
			break;
//			return 0;
		
		case load:
			cout << "Called LOAD\n" << endl;
			break;
//			return 1;
			
		case download:
			cout << "Called DOWNLOAD\n" << endl;
			break;
//			return 2;
			
		default:
			cout << "Command not found\n" << endl;
			break;
//			return -1;
	}
}
