#include <string>
#include "entity.h"
#include "enums.h"

Entity::Entity(){}
Entity::~Entity(){}

void Entity::AlterExp (int Amount){
	//Use this method to add experience to an entity.  This can add experience 
	//for a character, or be used to set the amount of experience an enemy
	//is worth.  (NOTE: A character's level cannot be manually set.  To manually
	//set an enemy's level, write a function in the enemy class to do so.)
	
	_Exp += Amount;    
	SetLevel();
}

int Entity::GetExp(){
	//Basic getter function to return Experience.
	
	return _Exp;    
}

int Entity::GetLevel(){
	//Basic getter function to return Level
	
	return _Level;    
}

void Entity::AlterGold (int Amount){
	//Alter the amount of gold the entity has on hand.
	
	_Gold += Amount;    
}

int Entity::GetGold(){
	//Basic getter function to return the amount of gold on hand.
	
	return _Gold;    
}
	
int Entity::GetStat(Stats Stat, bool Max){
	//Getter function for any stats defined in the stats enum.
	//This is implemented this way to make it easier to interact with spells and items classes.
	
	return StatTable[Max ? Maximum : Current][(int) Stat];    
}

void Entity::AlterStat (Stats Stat, bool Max, int Amount){
	//Relative setter function for stats.  (You can use this for absolute setting
	//by subtracting the existing value and adding the new value.)
	
	StatTable[Max ? Maximum : Current][(int) Stat] += Amount;
}

void Entity::SetStatToMax (Stats Stat){
	//Set the given stat's current value to it's max value.  Useful for healing,
	//mana replenishment, adverse effect restoration, etc.
	
	StatTable[Current][(int) Stat] = StatTable[Maximum][(int) Stat];
    
}

void Entity::SetLevel(){
	//Uses the current experience to set an entity's level.
	//If you want to manually set an enemy's level, write a
	//level setter function call and always call it after calling
	//AlterExp()
	
	int Prior;
	int Base = 100;
	int AugmentFactor = 0.35;
	int tExp = _Exp;

	_Level = 1;

	while (tExp > 1) {
		Prior = Prior * AugmentFactor + Base;
		tExp -= Prior;
		_Level++;
	}
}
