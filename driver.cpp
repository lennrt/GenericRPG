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
#include

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

	// Loop - Check mailbox for new actions
	
		//Check time table 
	
		//Game in progress action

		//Perform a character action

		//Perform an inventory action

		//Perform a world action

		//Perform targetting action

		//Perform update action only
	
		//Sleep 10 milliseconds before looping again.
    
    
}

void setupMemory(){

	
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


string StringToHex(string Data){
    string ReturnValue;
    string Hex("0123456789ABCDEF");
    unsigned char Hex1;
    unsigned char Hex2;
    unsigned char Char;

    for (int i = 0; i < Data.length(); i++){
        Char = Data[i];
        Hex1 = Hex[((int)Char) / 16];
        Hex2 = Hex[((int)Char) % 16];
        ReturnValue += Hex1;
        ReturnValue += Hex2;
    }
    return ReturnValue;
}

string HexToString(string Data){
    string ReturnValue = "";
    char Temp;

    for (int i = 0; i < Data.length(); i+=2){
        Temp = HexToInt(Data[i])*16 + HexToInt(Data[i+1]);
        ReturnValue += Temp;
    }
    return ReturnValue;
}

int HexToInt(char Convert){
    string Hex("0123456789ABCDEF");

    for (int i = 0; i < 16; i++){
        if (Convert == Hex[i]) return i;
    }
    return -1;
}

