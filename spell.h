#include <stdio.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include "enums.h"
#include "entity.h"

class Spell {

  public:

	Spell();
	~Spell();
	std::string get_title();
	std::string get_description();
	int get_range();
	void cast_spell(Entity& casting_char, Entity& target);
  /*  todo: 
    have spells modified by character stats e.g. fireball damage affected by int
    work on spells that temporarily alter stats
    
    hp changing spells: fireball, heal, frostbolt, powershot, fortify(temp), resurrect, thunderbolt
    stat altering: frostbolt, haste, haze, slow, radiance, fortify, focus, shield
    special: resurrect
  */
    
   private:
    
	std::string title;
	std::string description;
	int value;
	int mana_cost;
	int range;
	Stats target_stat;
    
};
