//
//  tile.cpp
//  tile
//
//  Created by Nhat Nguyen on 9/5/16.
//  Copyright © 2016 Nhat Nguyen. All rights reserved.
//

/*
 Title
 Description
 Possible enemies
 Possible static loot
 Tile type (generic or quest-based)
 Possible movement direction
 Climate
 */

#include "tile.h"

/* Tile Class Constructors */

Tile::Tile() {
    // Empty Constructor will randomly generate a Tile.
    generateTileType();
    generateClimateType();
    generateTitle();
    generateDescription();
    generateClimateDesc();
    generatePossibleEnemies();
    generateLoot();
    generatePossibleDirections();
}

Tile::Tile(string customTitle) {
    setTitle(customTitle);
    generateTileType();
    setDescription("Default description.");
    staticLoot = false;
    tileType = false;
}

Tile::Tile(string customTitle, string customDescription) {
    setTitle(customTitle);
    setDescription(customDescription);
    staticLoot = false;
    tileType = false;
}

Tile::Tile(string customTitle, string customDescription, vector<int> customEnemies) {
    setTitle(customTitle);
    setDescription(customDescription);
    setPossibleEnemies(customEnemies);
    staticLoot = false;
}

Tile::Tile(string customTitle, string customDescription, vector<int> customEnemies, bool loot, vector<int> customLoot) {
    setTitle(customTitle);
    setDescription(customDescription);
    setPossibleEnemies(customEnemies);
    staticLoot = loot;
    setLoot(customLoot);
}

Tile::Tile(string customTitle, string customDescription, vector<int> customEnemies, bool loot, vector<int> customLoot, bool customTileType) {
    setTitle(customTitle);
    setDescription(customDescription);
    setPossibleEnemies(customEnemies);
    staticLoot = loot;
    setLoot(customLoot);
    tileType = customTileType;
}

Tile::Tile(string customTitle, string customDescription, vector<int> customEnemies, bool loot, vector<int> customLoot, bool customTileType, vector<int> customDirections) {
    setTitle(customTitle);
    setDescription(customDescription);
    setPossibleEnemies(customEnemies);
    staticLoot = loot;
    setLoot(customLoot);
    tileType = customTileType;
    setPossibleDirections(customDirections);
}

Tile::Tile(string customTitle, string customDescription, vector<int> customEnemies, bool loot, vector<int> customLoot, bool customTileType, vector<int> customDirections, vector<int> customClimateDesc) {
    setTitle(customTitle);
    setDescription(customDescription);
    setPossibleEnemies(customEnemies);
    staticLoot = loot;
    setLoot(customLoot);
    tileType = customTileType;
    setPossibleDirections(customDirections);
    setClimateDesc(customClimateDesc);
}

/* Title Modifiers */

string Tile::getTitle() {
    return title;
}

void Tile::setTitle(string customTitle) {
    title = customTitle;
}

void Tile::generateTitle() {

}

/* Description Modifiers */

string Tile::getDescription() {
    return description;
}

void Tile::setDescription(string customDesc) {
    description = customDesc;
}

void Tile::generateDescription() {
    
}

/* Possible Enemies Modifiers */

vector<int> Tile::getPossibleEnemies() {
    return possibleEnemies;
}

void Tile::setPossibleEnemies(vector<int> customEnemies) {
    possibleEnemies = customEnemies;
}

void Tile::generatePossibleEnemies() {
    
}

/* Loot Modifiers */

vector<int> Tile::getLoot() {
    return possibleLoot;
}

void Tile::setLoot(vector<int> customLoot) {
    possibleLoot = customLoot;
}

void Tile::generateLoot() {
    
}

/* Tile Type Modifiers */

bool Tile::getTileType() {
    return tileType;
}

void Tile::setTileType(bool customeTileType) {
    tileType = customeTileType;
}

void Tile::generateTileType() {
    
}

/* Possible Directions Modifiers */

vector<int> Tile::getPossibleDirections() {
    return possibleDirections;
}

void Tile::setPossibleDirections(vector<int> customDirections) {
    possibleDirections = customDirections;
}

void Tile::generatePossibleDirections() {
    
}

/* Climate Type Modififers */

int Tile::getClimateType() {
    return climateType;
}

void Tile::setClimateType(int customClimateType) {
    climateType = customClimateType;
}

void Tile::generateClimateType() {
    
}

/* Climate Description Modifiers */

vector<int> Tile::getClimateDesc() {
    return climateDesc;
}

void Tile::setClimateDesc(vector<int> customClimate) {
    climateDesc = customClimate;
}

void Tile::generateClimateDesc() {
    
}

/* Pack & Unpack Functions */

string Tile::pack() {
    string packedString;
    return packedString;
}

void Tile::unpack(string packedString) {
    
}
