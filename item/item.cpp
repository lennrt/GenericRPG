#include <sstream>
#include <string>
#include "../enums.h"
	
/************************************************************************************
This is the base class for all items. It includes a description, affected stats,
value, range, type, and rarity. Item drops and skills haven't been implemented yet. 
*************************************************************************************/
class Item {
	protected:
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

	public:
		// Setters/getters for affected stats. We should assume that the presence of an
		// equipped item in a character's inventory simply boosts the character's stats.
		// When combat damage is computed, the item will be modifying the character's base
		// stats, so combat damage should simply take into account the final character stats 
		// without knowing anything about the item stats.

		// Getter function for description
    	std::string get_description() { 
    		return description;
    	}
    	
    	// Getter function for rarity
    	std::string get_rarity() { 
    		return rarity;
    	}
    	
    	// Getter function for itemType
    	std::string get_itemType() { 
    		return itemType;
    	}    

    	// retrieve the current or max value of the item stat in position "stat" of the ItemStats enum
    	int GetStat (Stats stat, bool Max) {
        	return StatTable[Max ? Maximum : Current][(int) stat];
    	}

    	// alter the current or max value of the stat by amount
    	void AlterStat (Stats Stat, bool Max, int Amount){
        	StatTable[Max ? Maximum : Current][(int) Stat] += Amount;
    	}
    
    	// save the current temporary state of a stat as a permanent state
    	void SetStatToMax (Stats Stat) {
        	StatTable[Current][(int) Stat] = StatTable[Maximum][(int)Stat];
    	}	
							
		// Getter for value
		int get_value() {
			return value;
		}

		// Setter for value
		void set_value(int newValue) {
			value = newValue;
		}

		// Getter for max_range
		int get_max_range() {
			return max_range;
		}

		// Setter for max_range
		void set_max_range(int newRange) {
			max_range = newRange;
		}

		// Getter for condition
		bool get_condition() { 
			return isBroken;
		}

		// Setter for condition
		void set_condition(bool condition) { 
			isBroken = condition;
		}

		// Stores value, max_range, length of rarity, rarity, length of description,
        // description, length of type, type, and isBroken 
        void write_to_stream(std::ostream & str) {          
            // Write value
            str.write(reinterpret_cast<char *>(&value),sizeof(value));
            
            // Write max_range
            str.write(reinterpret_cast<char *>(&max_range),sizeof(max_range));
            
            // Write length and data for rarity
            int rarity_length = rarity.length();
            str.write(reinterpret_cast<char *>(&rarity_length),sizeof(int));
            str.write(rarity.data(), rarity_length);
            
            // write length and data for description
            int description_length = description.length();
            str.write(reinterpret_cast<char *>(&description_length),sizeof(int));
            str.write(description.data(), description_length);
            
        	// Write length and data for itemType
            int itemType_length = itemType.length();
            str.write(reinterpret_cast<char *>(&itemType_length),sizeof(int));
            str.write(itemType.data(), itemType_length);
            
            // Write isBroken (1 for true 0 for false)
            str.write(reinterpret_cast<char *>(&isBroken),sizeof(bool));
            // todo: convert the bool to a number
        }

 		// Reads the data in the format written by Item::pack
        void read_from_file(std::istream & str) {
            const int BUFFER_SIZE = 256;
            static char buffer[256];
            
        	// Get value
            str.read(reinterpret_cast<char *>(&value),sizeof(value));
            
            // Get max_range
            str.read(reinterpret_cast<char *> (&max_range),sizeof(max_range));

            // Get the description's length, read the data into a local buffer, and assign to a variable
            int description_length;
            str.read(reinterpret_cast<char *>(&description_length),sizeof(int));
            str.read(buffer, description_length);
            buffer[description_length] = '\0';
            description = buffer;
            
            // Get the rarity's length, read the data into a local buffer, and assign to a variable
            int rarity_length;
            str.read(reinterpret_cast<char *>(&rarity_length),sizeof(int));
            str.read(buffer, rarity_length);
            buffer[rarity_length] = '\0';
            rarity = buffer;
            
            // Get the itemType's length, read the data into a local buffer, and assign to a variable
            int itemType_length;
            str.read(reinterpret_cast<char *>(&itemType_length),sizeof(int));
            str.read(buffer, itemType_length);
            buffer[itemType_length] = '\0';
            itemType = buffer;
            
            // Get the isBroken bool
            // todo
        }
        
        // This function converts a template data type to a string and adds 
        // a '/' to end of string as a delimiter.
    	template<typename T> std::string convert_to_string(T data){
    		std::stringstream stream;
    		std::string str;
    		stream << data;
    		stream >> str;
    		str += '/';
    		return str;
    	}
    	
    	// Pack() function packs every single member variable using the
    	// convert_to_string function and return a string containing all
    	// the data members
        std::string pack() {
            std::string retVal = "";
            
            // Convert value to string, add value string and '/' to reVal
            retVal+= convert_to_string(value);
        	
            // Convert max_range to string, add max_range string and '/' to retVal
            retVal += convert_to_string(max_range);
            
            // Add description to retVal string
            retVal+= description;
            retVal+='/';
            
            // Add rarity to retVal string
            retVal+= rarity;
            retVal+='/';
            
            // Add itemType to retVal string
            retVal+= rarity;
            retVal+='/';            
        
			// Add isBroken to retVal
			// todo

            return retVal;
        }
    	
    	// Unpack() function converts str to corresponding data type. It uses mem_var
    	// as a counter in the switch statement
        void unpack(std::string str) {
			int row;
        	int col;
        	std::string token;
        	std::istringstream ss(str);
        	int count = 1;
        	while(std::getline(ss, token, '/')) {
            	std::istringstream stream(token);
            	if (count == 1) {
                	stream >> value;
                	count++;
            	}
            	else if (count == 2) {
                	stream >> max_range;
                	count++;
            	}
            	else if (count == 3) {
            		// loop through the StatTable and unpack each value
                	stream >> StatTable[row][col++];
                	// once you have reached through all columns in the first row, move to the second row and reset the column
                	if (col = 14) {
                    	count++;
                    	row++;
                    	col = 0;
                	}
            	}
            	// loop through the second row of the StatTable after incrementing count by 1 in the previous else if block
            	else if(count == 4){
                	stream >> StatTable[row][col++];
                	if(col = 6){
                    	count++;
                	}
            	}
            	else if (count == 5) {
                	stream >> description;
                	count++;
            	}
            	else if (count == 6) {
                	stream >> rarity;
                	count++;
            	}
            	else if (count == 7) {
                	stream >> itemType;
                	count++;
            	}
            	else if( count == 8) {
                	stream >> isBroken;
                	break;
            	}
        	}
		}

};

int main() {
	return 0;
}