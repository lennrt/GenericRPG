#include <vector>

struct StatEffect {
   Stats Stat; 
   int Modifier;
   bool Permanent;
};

class Item {
    public:
    Item();
    ~Item();
    std::string GetName();
    void SetName(std::string newName); 
    int GetItemId();
    void SetItemId(int newId); 
    std::string GetDescription();  
    std::string GetRarity();  
    std::string GetItemType(); 
    void SetDescription(std::string newDesc);  
    void SetRarity(std::string newRarity);  
    void SetItemType(std::string newItemType);  
    int GetValue(); 
    void SetValue(int newValue); 
    int GetMaxRange(); 
    void SetMaxRange(int newRange);
    StatEffect GetStat(int degree);
    void SetStat(int degree, Stats Stat, int modifier, bool permanent);
    std::vector<StatEffect> GetStats();
    void SetStats(std::vector<StatEffect> effectsVector);
    
    private:
    std::string name;
    int itemId;
    int value;
    int max_range;
    std::string description;
    std::string rarity;
    std::string itemType;   
    std::vector<StatEffect> statEffects;
};
