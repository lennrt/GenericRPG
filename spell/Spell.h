class Spell {

  public:
  
    Spell();
    ~Spell();
   	string get_title();
    string get_description();
    int get_value();
    int get_mana_cost();
    int get_range();
    void cast_spell(Entity *casting_char, Entity *target);
    
   private:
    
    string title;
    string description;
    int value;
    int mana_cost;
    int range;
    stats target_stat;
    
};
