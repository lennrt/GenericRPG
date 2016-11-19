#include <string>
#include "entity.h"
#include "enums.h"


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

//Converts a template data type to a string and add
//the '|' character to end of string as delimiter.
template<typename T> std::string convert_to_string(T data){
    std::stringstream stream;
    std::string str;
    stream << data;
    stream >> str;
    str += '|';
    return str;
}


/***************************************************************
Virtual pack function to pack Exp, Level, and Stat Table using the
convert_to_string function and return a string containing all
the stats. Extra data should be packed before calling
Entity::pack() function.
 - The Character has to pack Gold and other needed data.
 - The Monster class has to pack Name.
***************************************************************/
virtual std::string pack(){
    //Convert Exp to String
    _retVal += convert_to_string(_Exp);
    
    //Convert Level to String
    _retVal += convert_to_string(_Level);
    
    //Convert Stat Table to String
    for(int row = 0; row < 2; row ++){
        for(int col = 0; col < 13; col++){
            _retVal += convert_to_string(StatTable[row][col]);
        }
    }
}

/*****************************************************************
 Virtual unpack() function to unpack exp, level, and stat table.
 Extra data should be unpack() before calling Entity::unpack()
  - The character has to unpack gold and other needed data.
  - The Monster Class has to unpack name.
 *****************************************************************/
virtual void unpack(std::string str)
{
    int row = 0 ;
    int col = 0;
    std::string token;
    std::istringstream ss(str);
    int count = 1;
    while(std::getline(ss, token, '|'))
    {
        std::istringstream stream(token);
        if (count == 1){
            stream >> _Exp;
            count++;
        }
        
        else if (count == 2){
            stream >> _Level;
            count++;
        }
        
        else{
            stream >> StatTable[row][col++];
            if (col == 13){
                    row++;
                    col = 0;
            }
        }
    }
}
