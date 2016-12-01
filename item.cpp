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

        // retrieve the primary, secondary, or tertiary StatEffect object (degree = 1 is primary, degree = 2 is secondary, etc.)
        StatEffect Item::GetStat (int degree) {
            return statEffects[degree-1];
        }

        // alter the specified stat
        void Item::SetStat (int degree, Stats Stat, int modifier, bool permanent) {
            StatEffect newStat;
            newStat.Stat = Stat;
            newStat.Modifier = modifier;
            newStat.Permanent = permanent;
            statEffects[degree -1] = newStat;
        }

        std::vector<StatEffect> Item::GetStats() {
            return statEffects;
        }

        void Item::SetStats(std::vector<StatEffect> effectsVector) {
            statEffects = effectsVector;
        }
