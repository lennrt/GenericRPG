#include <string>
#include <vector>
#include <time.h>
#include "entity.h"
#include "enums.h"

#ifndef TIMETABLE_H
#define TIMETABLE_H

using namespace std;

struct ScheduleItem{	
	int EffectID;	
	int EntityID;
	TimeTypes Type;
	string OtherData;
	time_t StartTime;
	double Duration;
};

class TimeTable{
    public:
        TimeTable();
        ~TimeTable();
	
	void AddItem(int NewEffectID, int NewEntityID, TimeTypes NewType, string NewOtherData, double NewDuration);
	bool SelectNextItem();
	void Pop();
	int TopEffectID();
	int TopEntityID();
	string TopOtherData();
	
    private:
	    vector<ScheduleItem> Table;
	    int Top;
	    bool TopSet;	
};

#endif
