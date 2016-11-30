#include<vector>

struct CsvItem {
    std::string name;
    int itemId;
    int value;
    int max_range;
    std::string description;
    std::string rarity;
    std::string itemType;   

    int stat1;
    int stat2;
    int stat3;
    int mod1;
    int mod2;
    int mod3;
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
    int GetStat (Stats stat, bool Max); 
    void AlterStat (Stats Stat, bool Max, int Amount);
    void SetStatToMax (Stats Stat); 
    int GetValue(); 
    void SetValue(int newValue); 
    int GetMaxRange(); 
    void SetMaxRange(int newRange); 
    void WriteToStream(std::ostream & str);          
    void ReadFromFile(std::istream & str); 
    template<typename T> std::string ConvertToString(T data);
    std::vector<Item> ConvertCsvItemToItem(std::vector<CsvItem> input);
    
    private:
    std::string name;
    int itemId;
    int value;
    int max_range;
    std::string description;
    std::string rarity;
    std::string itemType;   
    // This StatTable holds a row  for Current item stats and a row for Maximum item stats.
    // See enums.h for the ItemStats enum. 
    int StatTable[2][6]; 
    const int Current = 0; // temporarily affects the stat
    const int Maximum = 1; // permanently affects the stat
};


