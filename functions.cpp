#include "functions.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>

#define save 431
#define load 416
#define download 856
#define create 628
#define rm 648
#define details 742
#define open 434
#define ls 223
#define info 428
#define clear 519
#define exit 442

#define MAX_BLOCKSIZE 1024
#define MAX_SIZE 1073741824
using namespace std;

struct FS{
		long long int size;
		vector<string> file_list;
		int *ptr;
		int n_files = 0;
	};
	
bool FS_OPEN = false;	
FS curFS;

int toInt(char str[]){
	int value = 0;
	for(int i = 0; i < sizeof(str); i++){
		char t = str[i];
		value += (int)t;
	}
	return value;
}

signed int cmdCheck(char str[]){
	int index = toInt(str);
	switch(index){
		case save:
			cout << "Called SAVE\n" << endl;
			index  = 0;
			break;
		
		case load:
//			cout << "Called LOAD\n" << endl;
			index = 1;
			break;
			
		case download:
//			cout << "Called DOWNLOAD\n" << endl;
			index  = 2;
			break;

		case create:
//			cout << "Called CREATE\n" << endl;
			index = 3;
			break;
			
		case rm:
//			cout << "Called RM\n" << endl;
			index = 4;
			break;
			
		case details:
//			cout << "Called DETAILS\n" << endl;
			index = 5;
			break;
			
		case open:
//			cout << "Called OPEN\n" << endl;
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

void loadFunction(vector<string> param){
	if(param.size() < 3){
		cout << " > [ERROR] Not enough arguments in function LOAD... Usage: load <original_file.ext> <copy_file.ext> \n" << endl;
		return;
	}
	
	string original_filename = param[1];
	string copy_filename = param[2];
}

void downloadFunction(vector<string> param){
	if(param.size() < 4){
		cout << " > [ERROR] Not enough arguments in function DOWNLOAD... Usage: download <name> <copy_file.ext> <new_copy_file.ext>\n" << endl;
		return;
	}
	
	string name = param[1];
	string copy_file = param[2];
	string new_copy_file = param[3];
}

void createFunction(vector<string> param){
	if(param.size() < 4){
		cout << " > [ERROR] Not enough arguments in function CREATE... Usage: create <name> <blocksize> <nOfBlocks>\n" << endl;
		return;
	}
	
	string name = param[1];
	long long int b_size = stoi(param[2]);
	long long int nOfBlocks = stoi(param[3]);
	
	if(b_size > MAX_BLOCKSIZE){
		cout << " > [ERROR] Block size can't be over 1024! Default block sizes: 1024 512 256 128\n" << endl;
		return;
	}
	
	if( (b_size * nOfBlocks) > MAX_SIZE ){
		cout << " > [ERROR] Your current [ block size * number of blocks ] surpasses 1073741824 bytes or 1GB of memory.\n" << endl;
		return;
	}
	
	int *addr = (int*) malloc((b_size * nOfBlocks));
	if(addr == NULL){
		cout << " > [EXEC_ERROR] The file system couldn't be created. -> Memory ERR: Code (124)" << endl;
		return;
	}
	
	FS_OPEN = true;
	FS newFS;
	newFS.size = (b_size * nOfBlocks);
	newFS.ptr = addr;
	curFS = newFS;
				
}

void rmFunction(vector<string> param){
	if(param.size() < 2){
		cout << " > [ERROR] Not enough arguments in function OPEN... Usage: rm <filename.ext>\n" << endl;
		return;
	}
	
	string filename = param[1];
}

void detailsFunction(vector<string> param){
	if(param.size() < 2){
		cout << " > [ERROR] Not enough arguments in function OPEN... Usage: details <filename.ext>\n" << endl;
		return;
	}
	
	string filename = param[1];
}

void openFunction(vector<string> param){
	if(param.size() < 2){
		cout << " > [ERROR] Not enough arguments in function OPEN... Usage: open <name>\n" << endl;
		return;
	}
	
	string name = param[1];
}

void lsFunction(){
	
}

void infoFunction(){
	
}
