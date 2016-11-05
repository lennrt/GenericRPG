/********************************************************************************
 File name: monster.cpp
 Written by: Daniel Nguyen
 Written on 08/27/2016
 Purpose: This is a c++ file containing monster class.
 
 Class: CPSC 362
 *********************************************************************************/
#include <sstream>
#include <string>
#include "enum.h"
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
    Enemy(std::string str){
        unpack(str);
    };
    
    //Destructor
    ~Enemy();
    
    //Set the level of the monster
    void setLevel(int amount)
    {
        _Level = amount;
    }
    
    //Accessor function for name
    std::string get_name(){return name;}

    //Pack name then call Entity::pack() to pack the rest
    std::string pack(){
        this->_retVal += name;
        this->retVal += '|';
        Entity::pack();
        return _retVal;
    }
    
    //Unpack() function converts str to corresponding data type. It uses count
    //as a counter to store the correct member variable
    void unpack(std::string str)
    {
        //Unpack name
        std::string token;
        std::istringstream ss(str);
        std::getline(ss, token, '|')
        std::istringstream stream(token);
        stream >> name;
        
        //Calling Entity::unpack() to unpack the rest
        Entity::pack();
    }
};




