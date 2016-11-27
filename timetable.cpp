#include <string>
#include <vector>
#include <time.h>
#include "timetable.h"
#include "entity.h"
#include "enums.h"

using namespace std;

TimeTable::TimeTable(){
	TopSet = false;
}

TimeTable::~TimeTable(){
	
}	

void TimeTable::AddItem(int NewEffectID, int NewEntityID, TimeTypes NewType, string NewOtherData, double NewDuration){
	ScheduleItem Temp;
	
	Temp.EffectID = NewEffectID;
	Temp.EntityID = NewEntityID;
	Temp.Type = NewType;
	Temp.OtherData = NewOtherData;
	Temp.Duration = NewDuration;
	Temp.StartTime = time(NULL);
	
	Table.push_back(Temp);
}	

bool TimeTable::SelectNextItem(){
	//Select the item that has gone the longest time past it's duration.  
	//Return false if there are no items or if all items have passed less time than their durations.
	int MaxIndex = -1;
	double MaxTime;
	double Test;
	time_t CurrentTime = time(NULL);
	
	for (int i = 0; i < Table.size(); i++){
		Test = difftime(CurrentTime, Table[i].StartTime);
		Test -= Table[i].Duration;
		if (Test > 0){
			if (Test > MaxTime){
				MaxTime = Test;
				MaxIndex = i;
			}
		}	
	}
	
	if (MaxIndex > -1) {
		Top = MaxIndex;
		TopSet = true;
		return true;
	} else {
		return false;
	}
}	

void TimeTable::Pop(){
	if (TopSet){
		TopSet = false;
		Table.erase(Table.begin() + TopSet);
	}	
}	

int TimeTable::TopEffectID(){
	if (TopSet){
		return Table[Top].EffectID;
	}	
	return -1;
}	

int TimeTable::TopEntityID(){
	if (TopSet){
		return Table[Top].EntityID;
	}	
	return -1;	
}	

string TimeTable::TopOtherData(){
	string RetVal = "";
	if (TopSet){
		RetVal = Table[Top].OtherData;
	}	
	return "";	
}	
