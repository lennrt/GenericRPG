class Item {
    public:
	
    Item();
    ~Item();

    std::string GetName();

    int GetItemId(); 

    std::string GetDescription();  

    std::string GetRarity();  

    std::string GetItemType();  

    int GetStat (Stats stat, bool Max); 

    void AlterStat (Stats Stat, bool Max, int Amount);

    void SetStatToMax (Stats Stat); 

    int GetValue(); 

    void SetValue(int newValue); 

    int GetMaxRange(); 

    void SetMaxRange(int newRange); 

    bool GetCondition();  

    void SetCondition(bool condition);  

    void WriteToStream(std::ostream & str);          

    void ReadFromFile(std::istream & str); 

    template<typename T> std::string ConvertToString(T data);

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
	bool isBroken; // true indicates that the item is broken
	const int Current = 0; // temporarily affects the stat
	const int Maximum = 1; // permanently affects the stat
};
