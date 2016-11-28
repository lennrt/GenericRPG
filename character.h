#include <string>
#include <vector>
#include "enums.h"
#include "entity.h"
//#include "items.h"
//#include "spells.h"

struct PlayerItem{
	int ItemID;
	int Quantity;
};

struct PlayerEffect{
	Stats WhichStat;
	int Amount;
};

class Character : public Entity{
    public:
	std::string Race;
	std::string Class;
	std::string Sex;
	bool CanDoAction;
	bool CanCastspell;

	Character();	
	Character(std::string U, std::string C);
	~Character();
	void LoadCharacterFromFile();
	void SaveCharacterToFile();
	void CalculateDerivedStats();
	void CalculateTempBaseStats();
	void CalculateTempDerivedStats();
	void CalculateAllStats();
	int ApplyTempEffect(Stats WhichStat, int Amount);
	void EquipItem(int ItemID);
	void UnEquipItem(int ItemID);
	void LearnSpell(int SpellID);
	void GainItem(int ItemID, int Quantity);
	void LoseItem(int ItemID, int Quantity);
	int Damage(Entity& Target);
	
	std::string PackItems();
	std::string PackEquippedItems();
	std::string PackLearnedSpells();
	void UnpackItems(std::string Data);
	void UnpackEquippedItems(std::string Data);
	void UnpackLearnedSpells(std::string Data);

    private:
	bool fileExists(const std::string& file);
	std::string _U;     	//User
	std::string _C;    	//Character 
	std::vector<PlayerItem> PlayerItems;
	std::vector<PlayerItem> EquippedItems;
	std::vector<int> LearnedSpells;
	std::vector<PlayerEffect> PlayerEffects;

};
