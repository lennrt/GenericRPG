/********************************************************************************
File name: item.cpp
Written by: Lennart Rudolph
Written on 09/01/2016
Purpose: This is a C++ file containing classes for a few items.
Class: CPSC 362
*********************************************************************************/

#include <stdio.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
	
/************************************************************************************
This is the base class for all items. It includes a description, affected stats,
value, range, type, and rarity. Item drops and skills haven't been implemented yet. 
*************************************************************************************/
class Item {
	protected:
		int value;
		int max_range;
		int statBoosts[6]; // Each int corresponds to an attribute boost: {str, con, dex, int, wis, cha}
		string description;
		string rarity;
		string type;
		bool isBroken; // true indicates that the item is broken

	public:
		// Setters/getters for affected stats. We should assume that the presence of an
		// equipped item in a character's inventory simply boosts the character's stats.
		// When combat damage is computed, the item will be modifying the character's base
		// stats, so combat damage should simply take into account the final character stats 
		// without knowing anything about the item stats.
		int get_str_boost() {
			return statBoosts[0];
		}
		int get_con_boost() {
			return statBoosts[1];
		}
		int get_dex_boost() {
			return statBoosts[2];
		}
		int get_int_boost() {
			return statBoosts[3];
		}
		int get_wis_boost() {
			return statBoosts[4];
		}
		int get_cha_boost() {
			return statBoosts[5];
		}

		void set_str_boost(int str) {
			statBoosts[0] = str;
		}
		void set_con_boost(int con) {
			statBoosts[1] = con;
		}
		void set_dex_boost(int dex) {
			statBoosts[2] = dex;
		}
		void set_int_boost(int intel) {
			statBoosts[3] = intel;
		}
		void set_wis_boost(int wis) {
			statBoosts[4] = wis;
		}
		void set_cha_boost(int cha) {
			statBoosts[5] = cha;
		}								

		// Getter for value
		int get_value() {
			return value;
		}

		// Getter for value
		void set_value(int newValue) {
			value = newValue;
		}

		// Getter for max_range
		int get_max_range() {
			return max_range;
		}

		// Setter for max_range
		void set_max_range(int newRange) {
			max_range = newRange;
		}

		// Getter for type
		string get_type() {
			return type;
		}

		// Getter for rarity
		string get_rarity() {
			return rarity;
		}

		// Getter for description
		string get_description() {
			return description;
		}

		// Getter for condition
		bool get_condition() { 
			return isBroken;
		}

		// Setter for condition
		void set_condition(bool condition) { 
			isBroken = condition;
		}
};

/************************************************************************
The following classes contain information about a few different items.
*************************************************************************/
class Wooden_Sword : public Item
{
	public:
		Wooden_Sword() {
			this->value = 10;
			this->max_range = 3;
			// unfortunately we can't assign to an array from an initializer list like this:
			// this->statBoosts = {1, 0, 0, 0, 0, 0}; 
			this->statBoosts[0] = 1; // set str modifier to 1
			this->isBroken = false;
			this->type = "Shortsword";
			this->rarity = "Common";
			this->description = "An extremely simple sword made from a plank of wood";
		}
};

class Wooden_Dagger : public Item
{
	public:
		Wooden_Dagger() {
			this->value = 8;
			this->max_range = 2;
			this->statBoosts[2] = 1; // set dex modifier to 1
			this->isBroken = false;
			this->type = "Dagger";
			this->rarity = "Common";
			this->description = "An extremely simple dagger made from a half-plank of wood";
		}
};

class Wooden_Shield : public Item
{
	public:
		Wooden_Shield() {
			this->value = 15;
			this->max_range = 1;
			this->statBoosts[0] = 1;
			this->statBoosts[1] = 3;
			this->isBroken = false;
			this->type = "Shield";
			this->rarity = "Common";
			this->description = "An extremely simple shield made from a large slab of wood";
		}
};

class Wooden_Staff : public Item
{
	public:
		Wooden_Staff() {
			this->value = 12;
			this->max_range = 4;
			this->statBoosts[0] = 1;
			this->statBoosts[3] = 1;
			this->isBroken = false;
			this->type = "Staff";
			this->rarity = "Common";
			this->description = "An extremely simple staff made from a thin tree trunk. "
								"When you hold the staff, you think you feel slightly smarter...";
		}
};

class Wooden_Longbow : public Item
{
	public:
		Wooden_Longbow() {
			this->value = 10;
			this->max_range = 9;
			this->statBoosts[0] = 2;
			this->statBoosts[2] = 2;
			this->isBroken = false;
			this->type = "Longbow";
			this->rarity = "Common";
			this->description = "An extremely simple longbow fashioned out of wood and twigs";
		}
};

class Wooden_Shortbow : public Item
{
	public:
		Wooden_Shortbow() {
			this->value = 8;
			this->max_range = 6;
			this->statBoosts[0] = 1;
			this->statBoosts[2] = 3;
			this->isBroken = false;
			this->type = "Shortbow";
			this->rarity = "Common";
			this->description = "An extremely simple shortbow fashioned out of wood and twigs";
		}
};

int main() {
	Wooden_Sword wsw1;
	Wooden_Dagger wda1;
	Wooden_Shield wsh1;
	Wooden_Shortbow wsb1;
	Wooden_Longbow wlb1;
	Wooden_Staff wst1;
	cout << "You find a glowing pile of items on the ground. You pick up a wooden staff. As you wonder what the object is, a voice in the sky yells out: " << wst1.get_description();

	return 0;
}
