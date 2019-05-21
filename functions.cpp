#include "functions.h"
#include <iostream>
#define save 431
#define load 416
#define download 856
#define create 628
#define rm 648
#define details 742
#define open 657
#define ls 556
#define info 651
#define clear 519
#define exit 442
using namespace std;

int toInt(char str[]){
	int value = 0;
	for(int i = 0; i < sizeof(str); i++){
		char t = str[i];
		value += (int)t;
	}
	return value;
}

signed int cmdCheck(char str[]){
	cout << "\nReceived STR: " << str << endl;
	int index = toInt(str);
	cout << "STR Number: " << index << endl;
	cout << endl;
	switch(index){
		case save:
			cout << "Called SAVE\n" << endl;
			index  = 0;
			break;
		
		case load:
			cout << "Called LOAD\n" << endl;
			index = 1;
			break;
			
		case download:
			cout << "Called DOWNLOAD\n" << endl;
			index  = 2;
			break;

		case create:
			cout << "Called CREATE\n" << endl;
			index = 3;
			break;
			
		case rm:
			cout << "Called RM\n" << endl;
			index = 4;
			break;
			
		case details:
			cout << "Called DETAILS\n" << endl;
			index = 5;
			break;
			
		case open:
			cout << "Called OPEN\n" << endl;
			index = 6;
			break;
			
		case ls:
			cout << "Called LS\n" << endl;
			index = 7;
			break;
			
		case info:
			cout << "Called INFO\n" << endl;
			index = 8;
			break;
			
		case exit:
			cout << "Exitting...\n" << endl;
			index = -2;
			break;
			
		case clear:
			for(int i = 0; i < 30; i++){
				cout << endl;
			}
			index  = -3;
			break;
			
		default:
			cout << "Command not found\n" << endl;
			index = -1;
			break;
	}
	
	return index;
}

void saveFunction(){
	
}

void loadFunction(){
	
}

void downloadFunction(){
	
}

void createFunction(){
	
}

void rmFunction(){
	
}

void detailsFunction(){
	
}

void openFunction(){
	
}

void lsFunction(){
	
}

void infoFunction(){
	
}
