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
    std::string description;
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
    
    //Accessor function for description
    std::string get_description(){ return description;}
    
    
    //This function converts a template data type to a string and add
    //a '|' to end of string as delimiter.
    template<typename T> std::string convert_to_string(T data){
        std::stringstream stream;
        std::string str;
        stream << data;
        stream >> str;
        str += '|';
        return str;
    }
    
    //Pack() function packs every single member variable using the
    //convert_to_string function and return a string containing all
    //the stats
    std::string pack(){
        std::string retVal = "";
        //Add name and '/' following it to retVal string
        retVal += name;
        retVal += '|';
        
        //Convert Stat Table to String
        for(int row = 0; row < 2; row ++){
            for(int col = 0; col < 14; col++){
                retVal += convert_to_string(StatTable[row][col]);
            }
        }
        
        //Add description to retVal string
        retVal+= description;
        retVal+='|';
        
        return retVal;
    }
    
    //Unpack() function converts str to corresponding data type. It uses count
    //as a counter to store the correct member variable
    void unpack(std::string str)
    {
        int row = 0 ;
        int col = 0;
        std::string token;
        std::istringstream ss(str);
        int count = 1;
        while(std::getline(ss, token, '|'))
        {
            std::istringstream stream(token);
            if (count == 1){
                stream >> name;
                count ++;
            }
            else if (count == 2){
                stream >> StatTable[row][col++];
                if (col == 14){
                    if ( row == 0 ){
                        row++;
                        col = 0;
                    }
                    else
                        count++;
                }
            }
            
            else if( count == 3){
                stream >> description;
                break;
            }
        }
    }
};




