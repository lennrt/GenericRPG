#include <string>
#include <vector>
#include "character.h"


Character::AlterExp (int Amount){
    _Exp += Amount;    
    SetLevel(_Exp);
}

Character::GetExp(){
    return _Exp;    
}

Character::GetLevel(){
    return _Level;    
}

Character::AlterGold (int Amount){
    _Gold += Amount;    
}

Character::GetGold(){
    return _Gold;    
}
	
Character::GetStat(Stats Stat, bool Max){
    return StatTable[Max ? Maximum : Current][(int) Stat];    
}

Character::AlterStat (Stats Stat, bool Max, int Amount){
    StatTable[Max ? Maximum : Current][(int) Stat] += Amount;
}

Character::SetStatToMax (Stats Stat){
    StatTable[Current][(int) Stat] = StatTable[Maximum][(int) Stat]
    
}

Character::SetLevel(int tExp){
    int RetVal;
    int Prior;
    int Base = 100;
    int AugmentFactor = 0.35;
    
    while (tExp > 1) {
	Prior = Prior * AugmentFactor + Base;
	tExp -= Prior;
	RetVal++;
    }
    
    return RetVal;
}