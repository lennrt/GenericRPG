//
//  tile.hpp
//  tile
//
//  Created by Nhat Nguyen on 9/5/16.
//  Copyright © 2016 Nhat Nguyen. All rights reserved.
//

#ifndef tile_h
#define tile_h

#include <stdio.h>
#include <iostream>
#include <string>
#include <random>
#include <vector>

#include "enums.h"

using namespace std;

class Tile {
private:
    string title;
    
    // Description that will be printed out when tile is entered by Hero.
    string description;
    
    // Possible enemies stored as integers in vector.
    // Choose random integer from vector to spawn possible random enemy.
    vector<int> possibleEnemies;
    
    // Possible static loot default as false
    bool staticLoot;
    
    // Vector containing all possible loot
    vector<int> possibleLoot;
    
    // Tile type (generic or quest) with default as false = generic
    bool tileType;
    
    // Possible movement directions {1=forward, 2=back, 3=left, 4=right}
    vector<int> possibleDirections;
    
    // Climate description will be generated randomly based on library of strings
    vector<int> climateDesc;
    
public:
    int x;
    int y;
    // X & Y coordinates for the 2D Array
    
    // Tile class constructors
    Tile();
    Tile(string customTitle);
    Tile(string customTitle, string customDescription);
    Tile(string customTitle, string customDescription, vector<int> customEnemies);
    Tile(string customTitle, string customDescription, vector<int> customEnemies, bool loot, vector<int> customLoot);
    Tile(string customTitle, string customDescription, vector<int> customEnemies, bool loot, vector<int> customLoot, bool customTileType);
    Tile(string customTitle, string customDescription, vector<int> customEnemies, bool loot, vector<int> customLoot, bool customTileType, vector<int> customDirections);
    Tile(string customTitle, string customDescription, vector<int> customEnemies, bool loot, vector<int> customLoot, bool customTileType, vector<int> customDirections, vector<int> customClimate);
    
    // Title field modifiers
    string getTitle();
    void setTitle(string customTitle);
    void generateTitle();
    
    // Description field modifiers
    string getDescription();
    void setDescription(string customDescription);
    void generateDescription();
    
    
    // Possible Enemy  Vector modifiers
    vector<int> getPossibleEnemies();
    void setPossibleEnemies(vector<int> customEnemies);
    void generatePossibleEnemies();
    
    // Loot modifiers
    vector<int> getLoot();
    void setLoot(vector<int> customLoot);
    void generateLoot();
    
    // Tile Type modifiers
    bool getTileType();
    void setTileType(bool customTileType);
    void generateTileType();
    
    // Tile possible directions modifiers
    vector<int> getPossibleDirections();
    void setPossibleDirections(vector<int> customDirections);
    void generatePossibleDirections();
    
    // Climate field modifiers
    vector<int> getClimate();
    void setClimate(vector<int> customClimate);
    void generateClimate();
};


/* Random Element Selector (From a container) */

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    uniform_int_distribution<> dis(0, int(distance(start, end) - 1));
    advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static random_device rd;
    static mt19937 gen(rd());
    return select_randomly(start, end, gen);
}


#endif /* tile_hp */
