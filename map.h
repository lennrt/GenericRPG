//
//  map.h
//  map
//
//  Created by Nhat Nguyen on 11/27/16.
//  Copyright © 2016 Nhat Nguyen. All rights reserved.
//

#ifndef map_h
#define map_h

#include <stdio.h>
#include <iostream>
#include <random>
#include <vector>

#include "enums.h"
#include "tile.h"

using namespace std;

class Map {
	public:
		Map();
		~Map();
		void LoadMap(string MapFileName);
		int Point(int X, int Y);
		bool Passable(int X, int Y);
		string GetPlot(int X, int Y);
		
	private:
		int mapArray [100][100];
		int PassableThreshhold = 10;
		int MaxX = 99;
		int MaxY = 99;
		
	

};

#endif /* map_h */
