//
//  main.cpp
//  tile
//
//  Created by Nhat Nguyen on 9/5/16.
//  Copyright © 2016 Nhat Nguyen. All rights reserved.
//

#include <iostream>
#include <vector>
#include <iterator>
#include <random>

#include "tile.hpp"

using namespace std;

/* Testing */

int main(void) {
    // At start of game read in all text files.
    vector<string> titleAridVector;
    vector<string> titleForestVector;
    vector<string> titleWaterVector;
    
    vector<string> descriptionVector;
    
    vector<string> climateAridVector;
    vector<string> climateForestVector;
    vector<string> climateWaterVector;
    
    // Testing random element selecting from vector
    vector<int> myVector;
    myVector.push_back(1);
    myVector.push_back(2);
    myVector.push_back(3);
    myVector.push_back(4);
    myVector.push_back(5);
    // Chooses random element from vector.
    cout << "Random element: " << *select_randomly(myVector.begin(), myVector.end()) << endl << endl;
    
    // Testing tile class
    Tile startingTile;
    startingTile.setTileType(true);
    startingTile.setTitle("In a galaxy far far away... a galactic war rages on.");
    cout << startingTile.getTitle() << endl;
    startingTile.setDescription("You begin your journey on the planet Krypton in the small and humble town of Kal-el.");
    cout << startingTile.getDescription() << endl;
    
    for (int i = 0; i < 5; i++) {
        Tile myTile;
    }
    
    return 0;
}