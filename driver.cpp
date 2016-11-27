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

#include "entity.h"
#include "character.h"
#include "timetable.h"
#include "mailbox.h"

using namespace std;

//Structure for HTTP form data
struct FormInfo{
	string Key;
	string Value;
};

vector<Tile> Map; //[][]
vector<Enemy> SpawnedEnemies; // []

//Vector to hold Key / Value pairs after processing
vector<FormInfo> FormData;

void getFormData();

int main(){
	//Setup Game state
	
	//Load maps
	
	//Load definitions
	
	//Setup mailbox
	
	//Setup time table
	
	//Main Loop

		//Check Time table
	
		//Perform function for all expired times
	
		//Check Messages
	
		//Process Messages
	//Process incoming POST data
	//getFormData();  --->  Setup Mailbox

	//Load system state from shared memory
	setupMemory();



	//Check action based on POST:

	// Loop - Check mailbox for new actions
	
		//Check time table 
	
		//Game in progress action

		//Perform a character action

	string RetVal;	
		//Perform an inventory action

		//Perform a world action

		//Perform targetting action

		//Perform update action only
	
		//Sleep 10 milliseconds before looping again.
    
    
}


string GetValueFromKey(string FindKey){
	for (int i = 0; i < FormData.size(); i++){
		if (FormData[i].Key == FindKey){ return FormData[i].Value; }
	}	
	return "";
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

