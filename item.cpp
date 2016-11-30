#include <sstream>
#include <string>
#include "enums.h"
#include "item.h"
#include <vector>
    
/************************************************************************************
This is the base class for all items. It includes a description, affected stats,
value, range, type, and rarity. Item drops and skills haven't been implemented yet. 
*************************************************************************************/

        // Setters/getters for affected stats. We should assume that the presence of an
        // equipped item in a character's inventory simply boosts the character's stats.
        // When combat damage is computed, the item will be modifying the character's base
        // stats, so combat damage should simply take into account the final character stats 
        // without knowing anything about the item stats.


        // Getter function for item name
        std::string Item::GetName() { 
            return name;
        }

        void Item::SetName(std::string newName) {
            name = newName;
        } 

        void Item::SetItemId(int newId) {
            itemId = newId;
        } 


        // Getter function for description
        std::string Item::GetDescription() { 
            return description;
        }

        // Getter function for item ID
        int Item::GetItemId() { 
            return itemId;
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

        void Item::SetDescription(std::string newDesc) {
            description = newDesc;
        }  
        void Item::SetRarity(std::string newRarity) {
            rarity = newRarity;
        }  
        void Item::SetItemType(std::string newItemType) {
            itemType = newItemType;
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