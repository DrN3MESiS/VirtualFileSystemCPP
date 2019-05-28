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

struct FS_Block{
	int bid;
};

struct FS_File{
	string filename;
	vector<FS_Block> listOfBlocks;
};

struct FS{
		string name;
		long long int size;
		long long int freeBlocks;
		long long int usedBlocks = 0;
		int blocksize = 128;
		vector<FS_File> file_list;
		char * ptr;
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
//			cout << "Called SAVE\n" << endl;
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
//			cout << "Called INFO\n" << endl;
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
	if(FS_OPEN){
		ofstream output_file(curFS.name + ".dat", ios::binary);
	    output_file.write((char*)&curFS, sizeof(curFS));
	    output_file.close();
	} else {
		cout << " > [WARNING] There isn't a file system opened. Please load on create a file system in order to save.'\n" << endl;
	}
}

void loadFunction(vector<string> param){
	if(param.size() < 3){
		cout << " > [ERROR] Not enough arguments in function LOAD... Usage: load <original_file.ext> <copy_file.ext> \n" << endl;
		return;
	}
	if(!FS_OPEN){
		cout << " > [ERROR] There's no active file system... \n" << endl;
		return;
	}
	
	string original_filename = param[1];
	string copy_filename = param[2];
}

void downloadFunction(vector<string> param){
	if(param.size() < 3){
		cout << " > [ERROR] Not enough arguments in function DOWNLOAD... Usage: download <copy_file.ext> <new_copy_file.ext>\n" << endl;
		return;
	}
	
	if(!FS_OPEN){
		cout << " > [ERROR] There's no active file system... \n" << endl;
		return;
	}
	
	string copy_file = param[1];
	string new_copy_file = param[2];
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
	
	char *addr = (char*) malloc((b_size * nOfBlocks));
	if(addr == NULL){
		cout << " > [EXEC_ERROR] The file system couldn't be created. -> Memory ERR: Code (124)" << endl;
		return;
	}
	
	FS_OPEN = true;
	FS newFS;
	newFS.blocksize = b_size;
	newFS.name = name;
	newFS.size = (b_size * nOfBlocks);
	newFS.freeBlocks = nOfBlocks;
	newFS.ptr = addr;
	curFS = newFS;
	
	cout << " > [SUCCESS] A new file system was created -> " << curFS.name << endl;
}

void rmFunction(vector<string> param){
	if(param.size() < 2){
		cout << " > [ERROR] Not enough arguments in function OPEN... Usage: rm <filename.ext>\n" << endl;
		return;
	}
	
	if(!FS_OPEN){
		cout << " > [ERROR] There's no active file system... \n" << endl;
		return;
	}
	
	string filename = param[1];
}

void detailsFunction(vector<string> param){
	if(param.size() < 2){
		cout << " > [ERROR] Not enough arguments in function DETAILS... Usage: details <filename.ext>\n" << endl;
		return;
	}
	
	if(!FS_OPEN){
		cout << " > [ERROR] There's no active file system... \n" << endl;
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
	
	if(FS_OPEN){
		
		return;
	} else {
		ifstream input_file(name + ".dat", ios::binary);
    	FS master;
    	input_file.read((char*)&master, sizeof(master));
    	curFS = master;
	}
}

void lsFunction(){
	if(!FS_OPEN){
		cout << " > [ERROR] There's no active file system... \n" << endl;
		return;
	}
}

void infoFunction(){
	if(FS_OPEN){
		cout << "Current File System Information:" << endl;
		cout << "\tFile System Name: " << curFS.name << endl;
		cout << "\tFile System Size (bytes): " << curFS.size << endl;
		cout << "\tFile System Block Size: " << curFS.blocksize << endl;
		cout << "\tSpace Used (bytes): " << curFS.usedBlocks * curFS.blocksize << endl;
		cout << "\tFree Space (bytes): " << (curFS.freeBlocks * curFS.blocksize) << endl;
	} else {
		cout << " > [WARNING] There isn't a file system opened. Please load on create a file system in order to display it's information.\n" << endl;
	}
}
