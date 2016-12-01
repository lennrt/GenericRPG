#include <string>
#include <fstream>
#include "map.h"

using namespace std;

Map::Map() {}

Map::~Map() {}

void Map::LoadMap(string MapFileName){
	string Temp;
	fstream MapFile;
	int X = 0;
	int Y = 0;
	
	MapFile.open (MapFileName, fstream::in);
	while ( MapFile >> Temp ){
		mapArray[X][Y] = (unsigned short int)stoi(Temp);
		X++;
		if (X > MaxX){X = 0; Y++;}
	}
	MapFile.close();
}

int Map::Point(int X, int Y){
	return mapArray(X,Y);
}
bool Map::Passable(int X, int Y){
	return (mapArray(X,Y) < PassableThreshhold);
}

string Map::GetPlot(int X, int Y){
	//Returns a 20x20 chunk of the map
	string RetVal;
	string Temp;
	for (int i = X; i < X + 20; i++){
		for (int j = Y; j < Y + 20; j++){
			if (i <= MaxX && i > -1 && j <= MaxY && j > -1){
				Temp = to_string(mapArray(i,j));
				if (Temp.length() == 1) { RetVal += "0";}
				RetVal += Temp;
			} else {
			RetVal += "-1";
			}
		}
	}
	return RetVal;
}