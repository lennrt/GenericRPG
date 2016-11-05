class Item {
    public:
	    
	std::string Name;
	
    Item();
    ~Item();
	
	std::string Get_description();  

	std::string Get_rarity();  

	std::string Get_itemType();  

	int GetStat (Stats stat, bool Max); 

	void AlterStat (Stats Stat, bool Max, int Amount);

	void SetStatToMax (Stats Stat); 

	int Get_value(); 

	void Set_value(int newValue); 

	int Get_max_range(); 

	void Set_max_range(int newRange); 

	bool Get_condition();  

	void Set_condition(bool condition);  

    void Write_to_stream(std::ostream & str);          

    void Read_from_file(std::istream & str); 

	template<typename T> std::string Convert_to_string(T data);

    std::string Pack(); 

    void Unpack(std::string str); 


	private:
	int value;
	int max_range;
	// This StatTable holds a row  for Current item stats and a row for Maximum item stats.
	// See enums.h for the ItemStats enum. 
	int StatTable[2][6]; 
	std::string description;
	std::string rarity;
	std::string itemType;
	bool isBroken; // true indicates that the item is broken
	const int Current = 0; // temporarily affects the stat
	const int Maximum = 1; // permanently affects the stat
};