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

/*********************************************************************
 This is the monster class. It only uses Health, Experience, Attack,
 Defense, ActionCoolDown
 *********************************************************************/
class Enemy{
private:
    std::string name;
    int StatTable[2][9];
    const int Current = 0;
    const int Maximum = 1;
    std::string description;
public:
    //Accessor functions for hp
    int GetStat (Stats Stat, bool Max){
        return StatTable[Max ? Maximum : Current][(int) Stat];
    }
    
    void AlterStat (Stats Stat, bool Max, int Amount){
        StatTable[Max ? Maximum : Current][(int) Stat] += Amount;
    }
    
    void SetStatToMax (Stats Stat){
        StatTable[Current][(int) Stat] = StatTable[Maximum][(int)Stat];
    }
    //Accessor function for name
    std::string get_name(){return name;}
    
    //Accessor function for description
    std::string get_description(){ return description;}
    
    
    //This function converts a template data type to a string and add
    //a '/' to end of string as delimiter.
    template<typename T> std::string convert_to_string(T data){
        std::stringstream stream;
        std::string str;
        stream << data;
        stream >> str;
        str += '/';
        return str;
    }
    
    //Pack() function packs every single member variable using the
    //convert_to_string function and return a string containing all
    //the stats
    std::string pack(){
        std::string retVal = "";
        //Add name and '/' following it to retVal string
        retVal += name;
        retVal += '/';
        
        //Convert Stat Table to String
        for(int row = 0; row < 2; row ++){
            for(int col = 0; col < 2; col++){
                retVal += convert_to_string(StatTable[row][col]);
            }
        }
        
        //Add description to retVal string
        retVal+= description;
        retVal+='/';
        
        return retVal;
    }
    
    //Unpack() function converts str to corresponding data type. It uses count
    //as a counter to store the correct member variable
    void unpack(std::string str)
    {
        int row;
        int col;
        std::string token;
        std::istringstream ss(str);
        int count = 1;
        while(std::getline(ss, token, '/'))
        {
            std::istringstream stream(token);
            if (count == 1){
                stream >> name;
                count ++;
            }
            else if (count =2){
                stream >> StatTable[row][col++];
                if (col = 8){
                    count++;
                    row++;
                    col = 0;
                }
            }
            else if(count == 3){
                stream >> StatTable[row][col++];
                if(col = 8){
                    count++;
                }
            }
            
            else if( count ==4){
                stream >> description;
                break;
            }
        }
    }
};




