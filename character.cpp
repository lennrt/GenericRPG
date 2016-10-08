#include <string>
#include <vector>
#include "character.h"
#include "enums.h"


void Character::AlterExp (int Amount){
    _Exp += Amount;    
    SetLevel(_Exp);
}

int Character::GetExp(){
    return _Exp;    
}

int Character::GetLevel(){
    return _Level;    
}

void Character::AlterGold (int Amount){
    _Gold += Amount;    
}

int Character::GetGold(){
    return _Gold;    
}
	
int Character::GetStat(Stats Stat, bool Max){
    return StatTable[Max ? Maximum : Current][(int) Stat];    
}

void Character::AlterStat (Stats Stat, bool Max, int Amount){
    StatTable[Max ? Maximum : Current][(int) Stat] += Amount;
}

void Character::SetStatToMax (Stats Stat){
    StatTable[Current][(int) Stat] = StatTable[Maximum][(int) Stat];
    
}

int Character::SetLevel(int tExp){
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
