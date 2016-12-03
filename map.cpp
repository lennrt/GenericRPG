#include <string>
#include <fstream>
#include <iostream>
#include "map.h"

using namespace std;

Map::Map() {}

Map::~Map() {}

void Map::LoadMap(string MapFileName){
	string Temp;
	fstream MapFile;
	int X = 0;
	int Y = 0;
	int F = 0;
	int C = 0;
	
	MapFile.open (MapFileName, fstream::in);
	while ( MapFile >> Temp ){
		
				cout << Temp << endl << endl << endl << flush;
		for (int i = 0; i < Temp.length(); i++){
			if (Temp[i] == ','){
				C++;
				mapArray[X][Y] = stoi(Temp.substr(F,i-F));
				cout << mapArray[X][Y] << "  " << flush;
				X++;			
				F = i + 1;
			}
		}
		Y++; 
		X = 0;
				cout << "C = " << C << flush;
	}
	MapFile.close();
}

int Map::Point(int X, int Y){
	return (int)mapArray[X][Y];
}

bool Map::Passable(int X, int Y){
	return (mapArray[X][Y] < PassableThreshhold);
}

string Map::GetPlot(int X, int Y){
	//Returns a 20x20 chunk of the map
	string RetVal;
	string Temp;
	for (int i = X; i < X + 20; i++){
		for (int j = Y; j < Y + 20; j++){
			if (i <= MaxX && i > -1 && j <= MaxY && j > -1){
				Temp = to_string(mapArray[i][j]);
				if (Temp.length() == 1) { RetVal += "0";}
				RetVal += Temp;
			} else {
			RetVal += "-1";
			}
		}
	}
	return RetVal;
}