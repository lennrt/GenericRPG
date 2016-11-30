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
#include "monster.h"
#include "spell.h"
#include "item.h"
#include "tile.h"
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
vector<Character> Players;

//Vector to hold Key / Value pairs after processing
vector<FormInfo> FormData;

void getFormData(string Env);
string GetValueFromKey(string FindKey);
int GetPlayerByBox(string BoxNumber);

int main(){
	//Setup Game state
	TimeTable TimeTable;
	Mailbox Mailbox;
	bool Done = false;
	string Message;
	string Action;
	
	//Load maps
	
	//Load definitions
	cout << "Beginning main loop\n" << flush;
	cout << "Mailbox: " << Mailbox.SetupSuccessful() << "\n" << flush;
	//Main Loop
	while (!Done){
		FormData.clear();
		Action = "";
		
		//Check Time table.  Perform function for all expired times
		
		//Check and Process Messages
		Message = Mailbox.GetNextMessage();
		if (Message != "") { cout << Message; }
		getFormData(Message);
		Action = GetValueFromKey("Action");
		
		if (Action != ""){
			cout << "Intelligence:" << NewChar.GetStat(Intelligence, true) << "\n";
			cout << "Number of Open Boxes:" << Mailbox.BoxCount() << "\n";
			cout << "Number of Messages:" << Mailbox.MessageCount() << "\n";
		}
		
		if (Action == "EnterGame"){
			Character NewChar(GetValueFromKey("u"), GetValueFromKey("c"), stoi(GetValueFromKey("Box")));
			Mailbox.OpenUserBox(NewChar.Box);
			Mailbox.BroadcastMessage("This is a test of the server.");
			Mailbox.SendMessageToBox("Specific User Message", NewChar.Box);
			Players.push_back(NewChar);
		}
		
		if (Action == "RepeatMessage"){
			//This convoluted mess tests the message passing among objects (It's obv super redundant.)
			string Test = GetValueFromKey("Message") + " Repeated back at ya.";
			Mailbox.SendMessageToBox(Test , Players[GetPlayerByBox(GetValueFromKey("Box"))].Box);
			
		}
		
		if (Action == "LeaveGame"){
		}
		
		if (Action == "Move"){
		}	
		
		if (Action == "CastSpell"){
		}	
		
		if (Action == "EquipItem"){
		}		
		
		if (Action == "UseItem"){
		}		

		if (Action == "Attack"){
		}
		//Game in progress action

		//Perform a character action

		//Perform an inventory action

		//Perform a world action

		//Perform targetting action
	
		//Sleep 10 milliseconds before looping again.	
		
	}


	
	

    
    
}

int GetPlayerByBox(string BoxNumber){
	int FindBox = stoi(BoxNumber);
	for (int i = 0; i < Players.size(); i++){
		if (Players[i].Box == FindBox) return i;
	}
	return -1;
}

string GetValueFromKey(string FindKey){
	for (int i = 0; i < FormData.size(); i++){
		if (!FormData[i].Key.compare(FindKey)){ return FormData[i].Value; }
	}	
	return "";
}

void getFormData(string Env){
	int EnvLen = Env.size();	
	int Start = 1;
	int Mid = 0;
	FormInfo NewData;

	//Split Key-Value pairs and place in the FormData structure.
	for (int i = 1; i < EnvLen; i++){
	if (Env[i] == '='){Mid = i + 1;}
		if (Env[i] == '&' || i == EnvLen - 1){
			if (i == EnvLen - 1) i++;  //Get last character
			NewData.Key = Env.substr(Start,Mid-Start-1);
			NewData.Value = Env.substr(Mid, i - Mid);
			FormData.push_back(NewData);
			Start = i + 1;
		}
	}
}

