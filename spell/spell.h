#include <cstdlib>
#include "enums.h"
#include "entity.h"

class Spell {

  public:
  
    Spell();
    ~Spell();
   std::string get_title();
    std::string get_description();
    int get_value();
    int get_mana_cost();
    int get_range();
    void cast_spell(Entity *casting_char, Entity *target);
    
   private:
    
    std::string title;
    std::string description;
    int value;
    int mana_cost;
    int range;
    Stats target_stat;
    
};
