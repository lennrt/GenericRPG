#include <string>
#include <vector>
#include <fstream>
#include <sys/stat.h>
#include "character.h"
#include "enums.h"
#include "item.h"

using namespace std;

Character::Character(){
	CanCastspell = true;
	CanDoAction = true;
}

Character::Character(string U, string C, int B){
	CanCastspell = true;
	CanDoAction = true;
	_U = U;
	_C = C;
	Box = B;
	LoadCharacterFromFile();
}

Character::~Character(){}

void Character::LoadCharacterFromFile(){
	fstream CharFile;
	string Key;
	string Value;
	string Temp;
	vector<string> Line;
	
	CharFile.open ("u/" + _U + "/" + _C, fstream::in);
	while ( CharFile >> Temp ){
		Line.push_back(Temp);
	}
	CharFile.close();
	
	for (int i = 0; i < Line.size(); i++){
		for (int j = 0; j < Line[i].size(); j++){
			if (Line[i].at(j) == '='){
				Key = Line[i].substr(0,j);
				Value = Line[i].substr(j+1,Line[i].size() - j - 1);
				break;
			}
		}	
		if (Key == "Name"){Name = Value;}
		if (Key == "Race"){Race = Value;}
		if (Key == "Class"){Class = Value;}
		if (Key == "Sex"){Sex = Value;}
		
		if (Key == "Exp"){_Exp = stoi(Value);}
		if (Key == "Gold"){_Gold = stoi(Value);}
		
		if (Key == "Int"){StatTable[Maximum][(int)Intelligence] = stoi(Value);}
		if (Key == "Str"){StatTable[Maximum][(int)Strength] = stoi(Value);}
		if (Key == "Agi"){StatTable[Maximum][(int)Agility] = stoi(Value);}
		if (Key == "Con"){StatTable[Maximum][(int)Constitution] = stoi(Value);}
		if (Key == "Spd"){StatTable[Maximum][(int)Speed] = stoi(Value);}
		if (Key == "Cha"){StatTable[Maximum][(int)Charisma] = stoi(Value);}
		if (Key == "End"){StatTable[Maximum][(int)Endurance] = stoi(Value);}
		if (Key == "X"){X = stoi(Value);}
		if (Key == "Y"){Y = stoi(Value);}
		
		if (Key == "Items"){UnpackItems(Value);}
		if (Key == "EquippedItems"){UnpackEquippedItems(Value);}
		if (Key == "LearnedSpells"){UnpackLearnedSpells(Value);}		
	}
	
		CalculateAllStats();
}

void Character::SaveCharacterToFile(){
	fstream UserFile;
	fstream CharFile;
	vector<string> Rebuild;
	string Temp;
	
	UserFile.open ("u/" + _U + "/u", fstream::in);
	while ( UserFile >> Temp ){
		Rebuild.push_back(Temp);
	}
	UserFile.close();
	
	//Write out list of characters.  Update this character.
	UserFile.open ("u/" + _U + "/u", fstream::out | fstream::trunc);

	//Place current character at top of list.
	UserFile << _C << "\n";
	UserFile << Name << "\n";
	UserFile << to_string(GetLevel()) << "\n";
	UserFile << Race << "\n";
	UserFile << Class << "\n";
	
	for (int i = 0; i < Rebuild.size(); i++){
		if (i % 5 == 0 && Rebuild[i] == _C){i += 5;}
		if (i < Rebuild.size()) {UserFile << Rebuild[i] << "\n";}
	}
	UserFile.close();

	//Create the character information file for the character.
	CharFile.open ("u/" + _U + "/" + _C, fstream::out);
	
	CharFile << "Name=" << "Name" << "\n";
	CharFile << "Race=" << "Race" << "\n";
	CharFile << "Class=" << "Class" << "\n";
	CharFile << "Sex=" << "Sex" << "\n";
	
	CharFile << "Exp=" << _Exp << "\n";
	CharFile << "Gold=" << _Gold << "\n";
	
	CharFile << "Int=" << StatTable[Maximum][(int)Intelligence] << "\n";
	CharFile << "Str=" << StatTable[Maximum][(int)Strength] << "\n";
	CharFile << "Agi=" << StatTable[Maximum][(int)Agility] << "\n";
	CharFile << "Con=" << StatTable[Maximum][(int)Constitution] << "\n";
	CharFile << "Spd=" << StatTable[Maximum][(int)Speed] << "\n";
	CharFile << "Cha=" << StatTable[Maximum][(int)Charisma] << "\n";
	CharFile << "End=" << StatTable[Maximum][(int)Endurance] << "\n";
	CharFile << "X=" << to_string(X);
	CharFile << "Y=" << to_string(Y);
	
	CharFile << "Items=" << PackItems();
	CharFile << "EquippedItems=" << PackEquippedItems();
	CharFile << "LearnedSpells=" << PackLearnedSpells();

	CharFile.close();
}

string Character::PackItems(){
	string RetVal;
	for (int i = 0; i < PlayerItems.size(); i++){
		RetVal += PlayerItems[i].ItemID + ':' + PlayerItems[i].Quantity + ';';
	}
	return RetVal;
}

string Character::PackEquippedItems(){
	string RetVal;
	for (int i = 0; i < EquippedItems.size(); i++){
		RetVal += EquippedItems[i].ItemID + ':' + EquippedItems[i].Quantity + ';';
	}
	return RetVal;
}

string Character::PackLearnedSpells(){
	string RetVal;
	for (int i = 0; i < LearnedSpells.size(); i++){
		RetVal += LearnedSpells[i] + ",";
	}
	return RetVal;
}

void Character::UnpackItems(string Data){
	int SepPos = 0;
	vector<string> ItemList;
	std:string Key, Value;
	
	for (int i = 0; i < Data.size(); i++){
		if (Data.at(i) == ';'){
			ItemList.push_back(Data.substr(SepPos, Data.size() - SepPos - 1));
			SepPos = i + 1;
		}
	}
	
	for (int i = 0; i < ItemList.size(); i++){
		for (int j = 0; j < ItemList[i].size(); j++){
			if (ItemList[i].at(j) == ':'){
				Key = ItemList[i].substr(0,j);
				Value = ItemList[i].substr(j+1,ItemList[i].size() - j - 1);
				break;
			}
			PlayerItem Temp;
			Temp.ItemID = stoi(Key);
			Temp.Quantity = stoi(Value);
			PlayerItems.push_back(Temp);
		}
	}
}

void Character::UnpackEquippedItems(string Data){
	int SepPos = 0;
	vector<string> ItemList;
	std:string Key, Value;
	
	for (int i = 0; i < Data.size(); i++){
		if (Data.at(i) == ';'){
			ItemList.push_back(Data.substr(SepPos, Data.size() - SepPos - 1));
			SepPos = i + 1;
		}
	}
	
	for (int i = 0; i < ItemList.size(); i++){
		for (int j = 0; j < ItemList[i].size(); j++){
			if (ItemList[i].at(j) == ':'){
				Key = ItemList[i].substr(0,j);
				Value = ItemList[i].substr(j+1,ItemList[i].size() - j - 1);
				break;
			}
			PlayerItem Temp;
			Temp.ItemID = stoi(Key);
			Temp.Quantity = stoi(Value);
			EquippedItems.push_back(Temp);
		}
	}
}
void Character::UnpackLearnedSpells(string Data){
	int SepPos = 0;
	vector<string> ItemList;
	std:string Key, Value;
	
	for (int i = 0; i < Data.size(); i++){
		if (Data.at(i) == ','){
			LearnedSpells.push_back(stoi(Data.substr(SepPos, Data.size() - SepPos - 1)));
			SepPos = i + 1;
		}
	}
}

void Character::CalculateDerivedStats(){
	double Int = (double)StatTable[Current][(int)Intelligence];
	double Str = (double)StatTable[Current][(int)Strength];
	double Agi = (double)StatTable[Current][(int)Agility];
	double Con = (double)StatTable[Current][(int)Constitution];
	double Spd = (double)StatTable[Current][(int)Speed];
	double Cha = (double)StatTable[Current][(int)Charisma];
	double End = (double)StatTable[Current][(int)Endurance];
	
	StatTable[Maximum][(int)Health] = (10 + (Con * 0.8) + (End * 0.7) + (Str * 0.3));
	StatTable[Maximum][(int)Mana] = (10 + (Int * 0.8) + (End * 0.5));
	StatTable[Maximum][(int)Attack] = (10 + (Str * 0.9) + (Agi * 0.3) + (Spd * 0.5) + (End * 0.4));
	StatTable[Maximum][(int)Defense] = (10 + (Con * 0.8) + (Agi * 0.5) + (Spd * 0.3) + (End * 0.5));
	StatTable[Maximum][(int)ActionCoolDown] = (100 - (100 * (Spd/60)) - (100 * (End/90)) - (100 * (Agi/60)));
	StatTable[Maximum][(int)MagicCoolDown] = (100 -  (100 * (Spd/60)) - (100 * (Int/90)));
	
	StatTable[Maximum][(int)Health] = (int)((((double)_Level / 10) + 1) * StatTable[Maximum][(int)Health]);
	StatTable[Maximum][(int)Mana] = (int)((((double)_Level / 10) + 1) * StatTable[Maximum][(int)Mana]);
	StatTable[Maximum][(int)Attack] = (int)((((double)_Level / 10) + 1) * StatTable[Maximum][(int)Attack]);
	StatTable[Maximum][(int)Defense] = (int)((((double)_Level / 10) + 1) * StatTable[Maximum][(int)Defense]);
}

void Character::CalculateTempBaseStats(){
	
}

void Character::CalculateTempDerivedStats(){
}

int Character::ApplyTempEffect(Stats WhichStat, int Amount){
	//Returns the effect number so it can be reversed at timeout.
}

void Character::EquipItem(int ItemID){
}

void Character::CalculateAllStats(){
	SetLevel();
	SetAllStatsToMax();
	CalculateTempBaseStats();
	CalculateDerivedStats();
	CalculateTempDerivedStats();
}

void Character::UnEquipItem(int ItemID){
}

void Character::LearnSpell(int SpellID){
}

void Character::GainItem(int ItemID, int Quantity){
}

void Character::LoseItem(int ItemID, int Quantity){
}

int Character::Damage(Entity& Target){
}

bool fileExists(const string& file) {
	struct stat buf;
	return (stat(file.c_str(), &buf) == 0);
}