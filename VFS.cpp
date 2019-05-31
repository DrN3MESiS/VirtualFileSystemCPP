#include <iostream>
#include <cstring>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <map>
#define save 636
#define load 605
#define download 2948
#define create 1576
#define rm 109
#define details 2274
#define open 644
#define ls 115
#define info 647
#define clear 1057
#define exit 678
#define MAX_BLOCKSIZE 1024
#define MAX_SIZE 1073741824
#define version "\nVirtual File System [Version 0.1b]\nCreated by AEMN & GGM\n"
#define vol_max_size 1073741824

using namespace std;

signed int cmdCheck(char str[]);
void saveFunction();
void loadFunction(vector<string> param);
void downloadFunction(vector<string> param);
void createFunction(vector<string> param);
void rmFunction(vector<string> param);
void detailsFunction(vector<string> param);
void openFunction(vector<string> param);
void lsFunction();
void infoFunction();

class FS_Block{
	public:
		int bid;
		bool isFree = true;
};

class FS_File{
	public:
		string filename;
		int blocks_used = 0;
		vector<int> listOfBlocks;
};

class FS{
	public:
		string name;
		long long int size;
		long long int totalBlocks;
		long long int usedBlocks = 0;
		int blocksize = 128;
		map<string,FS_File> file_list;
		vector<FS_Block> usedB;
		char * ptr;
		void saveTo(const string& filename); 
    	void openFrom(const string& filename); 
	};
	
bool FS_OPEN = false;	
FS curFS;

int main(){
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

int toInt(char str[]){
	int value = 0;
	for(int i = 0; i < sizeof(str); i++){
		char t = str[i];
		value += (int)t * i;
	}
	return value;
}

signed int cmdCheck(char str[]){
	int index = toInt(str);
	switch(index){
		case save:
			index  = 0;
			break;
		
		case load:
			index = 1;
			break;
			
		case download:
			index  = 2;
			break;

		case create:
			index = 3;
			break;
			
		case rm:
			index = 4;
			break;
			
		case details:
			index = 5;
			break;
			
		case open:
			index = 6;
			break;
			
		case ls:
			index = 7;
			break;
			
		case info:
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

void FS::saveTo(const string& filename){
	
	ofstream of(filename, ios::binary);
    
    size_t value = name.size();
    of.write(reinterpret_cast<char*>(&value), sizeof(value));
    of.write(name.c_str(), value);

    of.write(reinterpret_cast<char*>(&size), sizeof(size));
    of.write(reinterpret_cast<char*>(&totalBlocks), sizeof(totalBlocks));
    of.write(reinterpret_cast<char*>(&usedBlocks), sizeof(usedBlocks));
    of.write(reinterpret_cast<char*>(&blocksize), sizeof(blocksize));

    value = file_list.size();
    of.write(reinterpret_cast<char*>(&value), sizeof(value));
    
	// write file_list[i] to the stream...
	for (auto it = file_list.begin(); it != file_list.end(); ++it) {
		/*string name = it->first;
		size_t tvalue = name.size();
    	of.write(reinterpret_cast<char*>(&tvalue), sizeof(tvalue));
    	of.write(name.c_str(), tvalue);

		FS_File temp = it->second;
		of.write(reinterpret_cast<char*>(&temp.blocks_used), sizeof(temp.blocks_used));
		tvalue = temp.filename.size();
		of.write(reinterpret_cast<char*>(&tvalue), sizeof(tvalue));
    	of.write(temp.filename.c_str(), tvalue);

    	tvalue = temp.listOfBlocks.size();
    	for(size_t t = 0; t < tvalue; t++){
    		of.write(reinterpret_cast<char*>(&temp.listOfBlocks[t]), sizeof(temp.listOfBlocks[t]));
		}*/
		
	}
	
	value = usedB.size();
	of.write(reinterpret_cast<char*>(&value), sizeof(value));
	for(size_t x = 0; x < value; x++){
		of.write(reinterpret_cast<char*>(&usedB[x]), sizeof(usedB[x]));
	}
	
	
    value = strlen(ptr);
    of.write(reinterpret_cast<char*>(&value), sizeof(value));
    of.write(ptr, value);
}

void FS::openFrom(const string& filename){
	ifstream inf(filename, ios::binary);
    size_t value;

    inf.read(reinterpret_cast<char*>(&value), sizeof(value));
    name.resize(value);
    inf.read(&name[0], value);

    inf.read(reinterpret_cast<char*>(&size), sizeof(size));
    inf.read(reinterpret_cast<char*>(&totalBlocks), sizeof(totalBlocks));
    inf.read(reinterpret_cast<char*>(&usedBlocks), sizeof(usedBlocks));
    inf.read(reinterpret_cast<char*>(&blocksize), sizeof(blocksize));

	// read file_list[i] from stream...
	value = file_list.size();
    inf.read(reinterpret_cast<char*>(&value), sizeof(value));
    
    for (auto const& x : file_list){
    	/*size_t tvalue;
    	//File Props reading
    	inf.read(reinterpret_cast<char*>(&tvalue), sizeof(tvalue));
		x.first.resize(tvalue);
    	inf.read(&x.first, value);
    	
    	//File class writting
		inf.read(reinterpret_cast<char*>(&x.blocks_used), sizeof(x.blocks_used));
		
		tvalue = temp.filename.size();
		inf.read(reinterpret_cast<char*>(&tvalue), sizeof(tvalue));
    	inf.read(temp.filename.c_str(), tvalue);
    	
    	tvalue = temp.listOfBlocks.size();
    	for(size_t t = 0; t < tvalue; t++){
    		inf.read(reinterpret_cast<char*>(&temp.listOfBlocks[t]), sizeof(temp.listOfBlocks[t]));
		}*/
	}
	
	value = usedB.size();
	inf.read(reinterpret_cast<char*>(&value), sizeof(value));
	for(size_t x = 0; x < value; x++){
		inf.read(reinterpret_cast<char*>(&usedB[x]), sizeof(usedB[x]));
	}


    inf.read(reinterpret_cast<char*>(&value), sizeof(value));
    free(ptr);
    ptr = (char*) malloc(value+1);
    inf.read(ptr, value);
    ptr[value] = '\0';
}

void saveFunction(){
	if(FS_OPEN){
  		curFS.saveTo(curFS.name + ".dat");    
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
	
	string original_filename = param[1];
	string copy_filename = param[2];
	
	ifstream input_file(original_filename, ios::binary);
	input_file.seekg(0, input_file.end);
	size_t length = input_file.tellg();
	input_file.seekg(0, input_file.beg);
	char buffer[length];
	
	FS_File f;
	f.filename = copy_filename;
	f.blocks_used = ceil((float)length / (float)curFS.blocksize);
	
	// don't overflow the buffer!
	if (length > (curFS.size - curFS.usedBlocks))
	{
	    cout << " > [ERROR] Not enough memory space for the file... Required a minimum memory of " << length << "\n" << endl;
		return;
	}
	
	input_file.read(buffer,sizeof(buffer));
	input_file.close();
	
	char block[curFS.blocksize];
	srand(time(NULL));
	int j;
	int b = 0;
	
	for(int i=1; i<length+1; i++){
		block[(i-1) - (b*curFS.blocksize)] = buffer[i-1];
		if(i % curFS.blocksize == 0 || i == length){
			b++;
			do{
				j = rand() % curFS.totalBlocks;
			}while(!curFS.usedB[j].isFree);
			curFS.usedB[j].isFree = false;
			f.listOfBlocks.insert(f.listOfBlocks.end(),j);
			for(int index=0; index < sizeof(block); index++){
				if(index > length){
					block[index] = '\0';
				}
				curFS.ptr[j*curFS.blocksize + index] = block[index];
			}
		}
	}
	curFS.file_list.insert(pair<string,FS_File>(f.filename,f));
	curFS.usedBlocks += f.blocks_used;

	cout << " > [SUCCESSFUL] The file has been loaded with success.'\n" << endl;
}

void downloadFunction(vector<string> param){
	if(param.size() < 3){
		cout << " > [ERROR] Not enough arguments in function DOWNLOAD... Usage: download <copy_file.ext> <new_copy_file.ext>\n" << endl;
		return;
	}
	
	string copy_file = param[1];
	string new_copy_file = param[2];
	
	FS_File f = curFS.file_list[copy_file];
	
	char buffer[curFS.blocksize * f.blocks_used];
	int j = 0;
	
	for (auto it = f.listOfBlocks.begin(); it != f.listOfBlocks.end(); ++it) {
		int n = *it;
		
		for(int index=0; index < curFS.blocksize; index++){
			buffer[j * curFS.blocksize + index] = curFS.ptr[n * curFS.blocksize + index];
		}
		j++;
	}
	
	ofstream output_file(new_copy_file);
    output_file.write(buffer, sizeof(buffer));
    output_file.close();
	
	cout << " > [SUCCESSFUL] The file has been downloaded with success.'\n" << endl;
}

void createFunction(vector<string> param){
	if(param.size() < 4){
		cout << " > [ERROR] Not enough arguments in function CREATE... Usage: create <name> <blocksize> <nOfBlocks>\n" << endl;
		return;
	}
	
	string name = param[1];
	long long int b_size = stoi(param[2]);
	long long int nOfBlocks = stoi(param[3]);
	
	if(b_size > MAX_BLOCKSIZE || b_size % 128 != 0){
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
	newFS.totalBlocks = nOfBlocks;
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
	FS_File f = curFS.file_list[filename];	
	
	if(f.blocks_used > 0){
		curFS.usedBlocks -= f.blocks_used;
		curFS.file_list.erase(filename);
		cout << " > [SUCCESSFUL] The file has been deleted with success.'\n" << endl;
	}else{
		cout << " > [ERROR] File not found... \n" << endl;
	}
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
	FS_File f = curFS.file_list[filename];	
	
	if(f.blocks_used > 0){
		cout << "Current File Information:" << endl;
		cout << "\tFile Name: " << f.filename << endl;
		cout << "\tNumber of Blocks Used: " << f.blocks_used << endl;
		cout << "\tBlocks List: " << endl;
		for (auto it = f.listOfBlocks.begin(); it != f.listOfBlocks.end(); ++it) 
	        cout << *it << " "; 
		cout << endl;
	}else{
		cout << " > [ERROR] File not found... \n" << endl;
	}
}

void openFunction(vector<string> param){
	if(param.size() < 2){
		cout << " > [ERROR] Not enough arguments in function OPEN... Usage: open <name>\n" << endl;
		return;
	}
	string name = param[1];
	curFS.openFrom(name + ".dat");
	FS_OPEN = true;
	cout << " > [SUCCESS] File system was loaded correctly into the system! \n" << endl;
}

void lsFunction(){
	if(!FS_OPEN){
		cout << " > [ERROR] There's no active file system... \n" << endl;
		return;
	}
	for(auto elem : curFS.file_list)
	{
	   cout << elem.second.filename << "\n";
	}
}

void infoFunction(){
	if(FS_OPEN){
		cout << "Current File System Information:" << endl;
		cout << "\tFile System Name: " << curFS.name << endl;
		cout << "\tFile System Size (bytes): " << curFS.size << endl;
		cout << "\tFile System Block Size: " << curFS.blocksize << endl;
		cout << "\tSpace Used (bytes): " << curFS.usedBlocks * curFS.blocksize << endl;
		cout << "\tFree Space (bytes): " << (curFS.totalBlocks * curFS.blocksize) << endl;
		cout << endl;
	} else {
		cout << " > [WARNING] There isn't a file system opened. Please load on create a file system in order to display it's information.\n" << endl;
	}
}
