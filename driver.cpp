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
#include "map.h"

using namespace std;

const int StartingX = 15;
const int StartingY = 15;

//Structure for HTTP form data
struct FormInfo{
	string Key;
	string Value;
};

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
	Map Map;
	bool Done = false;
	string Message;
	string Action;
	string Temp;
	
	//Load maps
	Map.LoadMap("map.csv");
	
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
			
		if (Action == "EnterGame"){
			Character NewChar(GetValueFromKey("u"), GetValueFromKey("c"), stoi(GetValueFromKey("b")));
			Mailbox.OpenUserBox(NewChar.Box);
			NewChar.X = StartingX;
			NewChar.Y = StartingY;
			Temp = "&Info=MyPosition&X=" + to_string(StartingX) + "&Y=" + to_string(StartingY);
			Mailbox.SendMessageToBox(Temp, NewChar.Box);
			Temp = "&Info=MapPlot&Plot=" + Map.GetPlot(NewChar.X - 9, NewChar.Y - 9);
			Mailbox.SendMessageToBox(Temp, NewChar.Box);
			Players.push_back(NewChar);
		}
		
		if (Action == "RepeatMessage"){
			//This convoluted mess tests the message passing among objects (It's obv super redundant.)
			string TestString = GetValueFromKey("Message") + " Repeated back at ya.";
			int TestBox = Players[GetPlayerByBox(GetValueFromKey("b"))].Box;
			cout << "Test:" << TestString << "\n";
			Mailbox.SendMessageToBox(TestString , TestBox );
			
		}
		
		if (Action == "LeaveGame"){
			Done = true;
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
	

		if (Action != ""){
			cout << "Number of Open Boxes:" << Mailbox.BoxCount() << "\n";
			cout << "Number of Messages:" << Mailbox.MessageCount() << "\n";
		}
		
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

