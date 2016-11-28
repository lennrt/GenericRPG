//Basic class for castable spells in the game
/*class Spell {
protected:
	string title;
	string description;
	int value;
	int mana_cost;
	int range;
	Stats target_stat;

public:
*/
#include <sstream>
#include <string>
#include "enums.h"
#include "spell.h"

	//get functions
	std::string Spell::get_title() {
		return title;
	}
	std::string Spell::get_description() {
		return description;
	}
	int Spell::get_range() {
		return range;
	}
	void Spell::cast_spell(Entity& casting_char, Entity& target)	{
		target.AlterStat(target_stat, false, value);
	}
	//todo: value dependent on casting character stats




//example spell

/* old; spells are in the table instead
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
*/
