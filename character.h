
#include <vector>
#include "enums.h"
//#include "items.h"
//#include "spells.h"

class Character{
    public:
	std::string Name;
	Races Race;
	Classes Class;
	//vector <Items> Inventory;
	//vector <Items> Equipped;
	
        Character();
        ~Character();
	
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
	int StatTable[5][2];
	
	const int Current = 0;
	const int Maximum = 1;
	
	void SetLevel(int tExp);
};
