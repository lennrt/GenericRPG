#include <sstream>
#include <string>
#include "enums.h"
#include "entity.h"
#include "monster.h"

//Constructor
Enemy::Enemy(){}

//Destructor
Enemy::~Enemy(){}

//Set the level of the monster
void Enemy::setLevel(int amount){
	_Level = amount;
}

//Accessor function for name
std::string Enemy::get_name(){
	return name;
}

//Setter function for name
void Enemy::set_name(std::string str)
{
	name = str;
}
