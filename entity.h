#include <string>
#include "enums.h"

#ifndef ENTITY_H
#define ENTITY_H

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

    private:
	int _Exp;
	int _Gold;
	int _Level;
	int StatTable[2][14];
	
	const int Current = 0;
	const int Maximum = 1;
	
	int SetLevel(int tExp);
};

#endif
