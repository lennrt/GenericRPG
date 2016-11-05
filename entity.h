#include <string>
#include "enums.h"

class Entity{
    public:
	    
	std::string Name;
	
        Entity();
        ~Entity();
	
	void AlterExp (int Amount);
	int GetExp();
	int GetLevel();
	void AlterGold (int Amount);
	int GetGold();
	
	int GetStat(Stats Stat, bool Max);
	void AlterStat (Stats Stat, bool Max, int Amount);
	void SetStatToMax (Stats Stat);
    virtual std::string pack();
    virtual void unpack(std::string);

    private:
	int _Exp;
	int _Gold;
	int _Level;
    std::string _retVal;
    int StatTable[2][13] = {0};
	
	const int Current = 0;
	const int Maximum = 1;
	
	int SetLevel(int tExp);
};
