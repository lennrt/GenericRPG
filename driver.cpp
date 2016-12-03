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

const int StartingX = 8;
const int StartingY = 8;

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
string GetNewCharInfo(Entity& Character);

int main(){
	//Setup Game state
	TimeTable TimeTable;
	Mailbox Mailbox;
	Map Map;
	bool Done = false;
	string Message;
	string Action;
	string Temp;
	int User;
	string Box;
	
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
		getFormData(Message);
		Action = GetValueFromKey("Action");
		Box = GetValueFromKey("Box");
		if (Box.length() > 0) User = GetPlayerByBox(Box);
			
		if (Action == "EnterGame"){
			Character NewChar(GetValueFromKey("u"), GetValueFromKey("c"), stoi(GetValueFromKey("b")));
			Mailbox.OpenUserBox(NewChar.Box);
			NewChar.X = StartingX;
			NewChar.Y = StartingY;
			Temp = "&Op=MyPosition&X=" + to_string(StartingX) + "&Y=" + to_string(StartingY);
			Mailbox.SendMessageToBox(Temp, NewChar.Box);
			Mailbox.BroadcastMessage("&Op=Con&Message=" + NewChar.Name + " has entered the game.");
			Temp = GetNewCharInfo(NewChar);
			Mailbox.BroadcastMessage(GetNewCharInfo(NewChar));
			for (int i = 0; i < Players.size(); i++){
				Mailbox.SendMessageToBox(GetNewCharInfo(Players[i]), NewChar.Box);
			}
			Players.push_back(NewChar);
		}
		
		if (Action == "RepeatMessage"){
			//This convoluted mess tests the message passing among objects (It's obv super redundant.)
			string TestString = "&Op=Alert&Message=" + GetValueFromKey("Message") + " Repeated back at ya.";
			int TestBox = Players[GetPlayerByBox(GetValueFromKey("b"))].Box;
			cout << "Test:" << TestString << "\n";
			Mailbox.SendMessageToBox(TestString , TestBox );
			
		}
		
		if (Action == "LeaveGame"){
			//Done = true;
			Mailbox.CloseUserBox(stoi(GetValueFromKey("b"));
		}
		
		if (Action == "GetPlot"){
			int X = stoi(GetValueFromKey("X"));
			int Y = stoi(GetValueFromKey("Y"));
			Temp = "&Op=MapPlot&X=" + GetValueFromKey("X") + "&Y=" + GetValueFromKey("Y") + "&Plot=" + Map.GetPlot(X,Y);
			Mailbox.SendMessageToBox(Temp, Players[User].Box);
		}
		
		if (Action == "Move"){
			int Who = GetPlayerByBox(GetValueFromKey("b"));
			int X = stoi(GetValueFromKey("XMove"));
			int Y = stoi(GetValueFromKey("YMove"));
			if (Map.Passable(Players[Who].X + X, Players[Who].Y + Y)){
				string Temp = "&Op=PlayerMove&b=" + GetValueFromKey("b") + "&X=" + GetValueFromKey("XMove") + "&Y=" + GetValueFromKey("YMove");
				Mailbox.BroadcastMessage(Temp);
			}
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

string GetNewCharInfo(Character& Character){
	string RetVal;
	RetVal += "&Op=UpdateChar&b=" + to_string(Character.Box);
	RetVal += "&cInt=" + to_string(Character.GetStat(Intelligence, false));
	RetVal += "&cStrt=" + to_string(Character.GetStat(Strength, false));
	RetVal += "&cAgi=" + to_string(Character.GetStat(Agility, false));
	RetVal += "&cCon=" + to_string(Character.GetStat(Constitution, false));
	RetVal += "&cSpd=" + to_string(Character.GetStat(Speed, false));
	RetVal += "&cCha=" + to_string(Character.GetStat(Charisma, false));
	RetVal += "&cEnd=" + to_string(Character.GetStat(Endurance, false));
	RetVal += "&cHea=" + to_string(Character.GetStat(Health, false));
	RetVal += "&cMan=" + to_string(Character.GetStat(Mana, false));
	RetVal += "&cAtt=" + to_string(Character.GetStat(Attack, false));
	RetVal += "&cDef=" + to_string(Character.GetStat(Defense, false));
	RetVal += "&cACD=" + to_string(Character.GetStat(ActionCoolDown, false));
	RetVal += "&cMCD=" + to_string(Character.GetStat(MagicCoolDown, false));
	
	RetVal += "&mInt=" + to_string(Character.GetStat(Intelligence, true));
	RetVal += "&mStrt=" + to_string(Character.GetStat(Strength, true));
	RetVal += "&mAgi=" + to_string(Character.GetStat(Agility, true));
	RetVal += "&mCon=" + to_string(Character.GetStat(Constitution, true));
	RetVal += "&mSpd=" + to_string(Character.GetStat(Speed, true));
	RetVal += "&mCha=" + to_string(Character.GetStat(Charisma, true));
	RetVal += "&mEnd=" + to_string(Character.GetStat(Endurance, true));
	RetVal += "&mHea=" + to_string(Character.GetStat(Health, true));
	RetVal += "&mMan=" + to_string(Character.GetStat(Mana, true));
	RetVal += "&mAtt=" + to_string(Character.GetStat(Attack, true));
	RetVal += "&mDef=" + to_string(Character.GetStat(Defense, true));
	RetVal += "&mACD=" + to_string(Character.GetStat(ActionCoolDown, true));
	RetVal += "&mMCD=" + to_string(Character.GetStat(MagicCoolDown, true));
	
	RetVal += "&Level=" + Character.GetLevel();
	RetVal += "&Exp=" + Character.GetExp();
	RetVal += "&Gold=" + Character.GetGold();
	RetVal += "&X=" + Character.X;
	RetVal += "&Y=" + Character.Y;
	RetVal += "&Name=" + Character.Name;
	RetVal += "&Race=" + Character.Race;
	RetVal += "&Class=" + Character.Class;
	RetVal += "&Sex=" + Character.Sex;
	
	return RetVal;
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

