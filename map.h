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
private:
    unsigned short int mapArray [100][100];
    
public:
    Map();
};

#endif /* map_h */
