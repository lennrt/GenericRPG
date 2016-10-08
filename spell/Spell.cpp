#include <stdio.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include "enums.h"
using namespace std;

//Basic class for castable spells in the game
class Spell {
protected:
	string title;
	string description;
	int value;
	int mana_cost;
	int range;
	stats target_stat;

public:
	//get functions
	string get_title() {
		return title;
	}
	string get_description() {
		return description;
	}
	int get_value() {
		return value;
	}
	int get_mana_cost() {
		return mana_cost;
	}
	int get_range() {
		return range;
	}
	void cast_spell(obj *casting_char, obj *target)	{
		target -> AlterStat(target_stat, value);
	}

};


//example spell
class fireball : public Spell
{
public:
	fireball() {
		this->value = 5;
		this->range = 3;
		this->mana_cost = 5;
		this->title = "Fireball";
		this->description = "Basic fireball";
	}
};
