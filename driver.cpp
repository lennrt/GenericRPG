#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <chrono>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <unistd.h>

using namespace std;

//Structure for HTTP form data
struct FormInfo{
	string Key;
	string Value;
};

//Vector to hold Key / Value pairs after processing
vector<FormInfo> FormData;

void setupMemory();
size_t getControlSize();
void getFormData();

int main(){

	//Redirect Error messages to stdout - This will cause them to appear on the web page
	dup2(STDOUT_FILENO, STDERR_FILENO);
	exit(at_quick_exit());
	
	//Set HTTP Header
	cout << "Content-type: text/plain\n\r\n\r";

	//Process incoming POST data
	getFormData();

	//Load system state from shared memory
	setupMemory();



	//Check action based on POST:

	//User login

	//User setup

	//Character login

	//Character setup

	//Game in progress action

	//Perform a character action

	//Perform an inventory action

	//Perform a world action

	//Perform targetting action

	//Perform update action only
    
    
}

void setupMemory(){
	//This function should be protected by a semaphore    -   release before static **************
	
	//Shared memory sections:  	control (global variables)
	//				static (tables of class types)
	//				dynamic (spawned enemies, objects, tiles)
	//				character (one for each character.)
	
	//shared Memory ID and pointer for control segment.
	int controlID;
	char* controlPointer;
	
	//Existing session or new session.
	bool New = true;

	//Randomly generated key value for shared memory: 920004285
	key_t controlKey = 920004285;
	
	//Calculate the size of the command portion of shared memory.
	size_t controlSize = getControlSize();
    
	//This will attempt to create a brand new shared memory segment and fail if one exists.
	//This should only succeed the first time and fail every other time (as a session should exist.)
	
	//Attempt to create a new memory segment.
	controlID = shmget(controlKey, controlSize, S_IRUSR | S_IWUSR | IPC_CREAT | IPC_EXCL);
	
	//If exclusive create fails, it should be because the segment exists.  Try a normal create and attach to existing.
	if (controlID == -1){
		controlID = shmget(controlKey, controlSize, S_IRUSR | S_IWUSR);
		
		//If it fails this time, the error is unknown.
		if (controlID == -1){
			//Fatal error.
			cout << "Unknown error with shmget on existing section of memory set aside for conotrol.\n\r\n\r";
			exit(-1);
		}
		//Existing game session.
		New = false;
	}
	
	//Attach to the memory segment.
	controlPointer = (char*)shmat(controlID, NULL, 0);
	
	if (New) {
		//Is this the first time ever running the program or did the system restart.
		
	} else {
		//Load class tables from files and place in shared memory.
		
		//
		
	}
	
}

size_t getControlSize(){
}

void getFormData(){
	int EnvLen = atoi(getenv("CONTENT_LENGTH"));
	int Start = 0;
	int Mid = 0;
	FormInfo NewData;
	string Env;

	//cin can technically recieve more than CONTENT_LENGTH.
	//We'll use EnvLen to restrict what we read.
	cin >> Env;

	if (EnvLen == 0){
		//Improper header
		cout << "Data not received";
		exit(-1);
	}

	//Split Key-Value pairs and place in the FormData structure.
	for (int i = 1; i < EnvLen; i++){
	if (Env[i] == '='){Mid = i + 1;}
		if (Env[i] == '&' || i == EnvLen - 1){
			if (i == EnvLen - 1) i++;  //Get last character
			NewData.Key = Env.substr(Start,Mid-Start-1);
			NewData.Value = HexToString(Env.substr(Mid, i - Mid));
			FormData.push_back(NewData);
			Start = i + 1;
		}
	}
}
