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

class FS_Block{
	public:
		int bid;
		bool isFree = true;
};

class FS_File{
	public:
		string filename;
		vector<FS_Block> listOfBlocks;
};

class FS{
	public:
		string name;
		long long int size;
		long long int freeBlocks;
		long long int usedBlocks = 0;
		int blocksize = 128;
		vector<FS_File> file_list;
		char * ptr;
		void save(ofstream& of); 
    	void open(ifstream& inf); 
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

void FS::save(ofstream& of){ 
  of.write(&name, sizeof(name)); 
  of.write(&size, sizeof(size));
  of.write(&freeBlocks, sizeof(freeBlocks)); 
  of.write(&usedBlocks, sizeof(usedBlocks)); 
  of.write(&blocksize, sizeof(blocksize)); 
  of.write(&file_list, sizeof(file_list));
  of.write((char *)&ptr, sizeof(ptr));
}

void FS::open(ifstream& inf){ 
  inf.read(&name, sizeof(name)); 
  inf.read(&size, sizeof(size));
  inf.read(&freeBlocks, sizeof(freeBlocks)); 
  inf.read(&usedBlocks, sizeof(usedBlocks)); 
  inf.read(&blocksize, sizeof(blocksize)); 
  inf.read(&file_list, sizeof(file_list));
  inf.read((char *)&ptr, sizeof(ptr));
} 

void saveFunction(){
	if(FS_OPEN){
		ofstream outfile;
		string filename = curFS.name + ".dat";
  		outfile.open(filename, ios::binary | ios::out);
  		curFS.save(outfile);
	    outfile.close();
	    
	    FS_OPEN = false;
	    cout << " > [SUCCESS] File system was saved successfully.'\n" << endl;
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
	
	
	FS newFS;
	newFS.blocksize = b_size;
	newFS.name = name;
	newFS.size = (b_size * nOfBlocks);
	newFS.freeBlocks = nOfBlocks;
	newFS.ptr = (char*) malloc((b_size * nOfBlocks));
	
	if(newFS.ptr == NULL){
		cout << " > [EXEC_ERROR] The file system couldn't be created. -> Memory ERR: Code (124)" << endl;
		return;
	}
	
	for(int i = 0; i < newFS.size; i++){
		newFS.ptr[i] = '0';
	}
	
	FS_OPEN = true;
	curFS = newFS;
	
	cout << " > [SUCCESS] A new file system was created -> " << curFS.name << "\n" << endl;
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
	
	ifstream inFile;
	inFile.open(name + ".dat", ios::binary|ios::in);
	
	if(inFile.fail()){
		cout << " > [ERROR] There's an error trying to read that file...\n" << endl;
		return;
	}
	curFS.open(inFile);
	cout << " > [SUCCESS] File system was loaded correctly into the system! \n" << endl;
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
		cout << endl;
	} else {
		cout << " > [WARNING] There isn't a file system opened. Please load on create a file system in order to display it's information.\n" << endl;
	}
}
