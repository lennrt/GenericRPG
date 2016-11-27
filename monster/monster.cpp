/********************************************************************************
 File name: monster.cpp
 Written by: Daniel Nguyen
 Written on 08/27/2016
 Purpose: This is a c++ file containing monster class.
 
 Class: CPSC 362
 *********************************************************************************/
#include <sstream>
#include <string>
#include "enums.h"
#include "entity.h"

/*********************************************************************
 This is the monster class. It only uses Health, Experience, Attack,
 Defense, ActionCoolDown.
 *********************************************************************/
class Enemy : public Entity{
private:
    std::string name;
public:
    //Constructor
    Enemy();
    
    //Destructor
    ~Enemy();
    
    //Set the level of the monster
    void setLevel(int amount)
    {
        _Level = amount;
    }
    
    //Accessor function for name
    std::string get_name(){return name;}
};




