#include <sstream>
#include <string>
#include "enums.h"
#include "entity.h"
#include "monster.h"

//Set the level of the monster
void Enemy::setLevel(int amount){
	_Level = amount;
}

//Accessor function for name
std::string Enemy::get_name(){
	return name;
}
