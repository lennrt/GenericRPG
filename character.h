#include <string>
#include <vector>
#include "enums.h"
#include "entity.h"
//#include "items.h"
//#include "spells.h"

class Character : public Entity{
    public:
	Races Race;
	Classes Class;
	//vector <Items> Inventory;
	//vector <Items> Equipped;
	
        Character();
        ~Character();

    private:

};
