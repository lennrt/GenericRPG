#include <sstream>
#include <string>
#include "../enums.h"
#include "item.h"
	
/************************************************************************************
This is the base class for all items. It includes a description, affected stats,
value, range, type, and rarity. Item drops and skills haven't been implemented yet. 
*************************************************************************************/

		// Setters/getters for affected stats. We should assume that the presence of an
		// equipped item in a character's inventory simply boosts the character's stats.
		// When combat damage is computed, the item will be modifying the character's base
		// stats, so combat damage should simply take into account the final character stats 
		// without knowing anything about the item stats.

		// Getter function for description
    	std::string Item::GetDescription() { 
    		return description;
    	}
    	
    	// Getter function for rarity
    	std::string Item::GetRarity() { 
    		return rarity;
    	}
    	
    	// Getter function for itemType
    	std::string Item::GetItemType() { 
    		return itemType;
    	}    

    	// retrieve the current or max value of the item stat in position "stat" of the ItemStats enum
    	int Item::GetStat (Stats stat, bool Max) {
        	return StatTable[Max ? Maximum : Current][(int) stat];
    	}

    	// alter the current or max value of the stat by amount
    	void Item::AlterStat (Stats Stat, bool Max, int Amount){
        	StatTable[Max ? Maximum : Current][(int) Stat] += Amount;
    	}
    
    	// save the current temporary state of a stat as a permanent state
    	void Item::SetStatToMax (Stats Stat) {
        	StatTable[Current][(int) Stat] = StatTable[Maximum][(int)Stat];
    	}	
							
		// Getter for value
		int Item::GetValue() {
			return value;
		}

		// Setter for value
		void Item::SetValue(int newValue) {
			value = newValue;
		}

		// Getter for max_range
		int Item::GetMaxRange() {
			return max_range;
		}

		// Setter for max_range
		void Item::SetMaxRange(int newRange) {
			max_range = newRange;
		}

		// Getter for condition
		bool Item::GetCondition() { 
			return isBroken;
		}

		// Setter for condition
		void Item::SetCondition(bool condition) { 
			isBroken = condition;
		}

		// Stores value, max_range, length of rarity, rarity, length of description,
        // description, length of type, type, and isBroken 
        void Item::WriteToStream(std::ostream & str) {          
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
        void Item::ReadFromFile(std::istream & str) {
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
    	template<typename T> std::string Item::ConvertToString(T data){
    		std::stringstream stream;
    		std::string str;
    		stream << data;
    		stream >> str;
    		str += '/';
    		return str;
    	}

int main() {
	return 0;
}
