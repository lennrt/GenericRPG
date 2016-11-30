#include <sstream>
#include <string>
#include "enums.h"
#include <istream>
#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include "item.h"

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

std::vector<CsvItem> GenerateCsvItems() {

    std::string line;
    std::string namefile = "items.csv";

    std::ifstream file;

    file.open(namefile);

    if( !file.is_open()) {

        std::cout << "File "<< namefile <<" not found." << std::endl;
        exit(-1);

    }

    std::vector<CsvItem> items; 

for (CsvItem i;
      std::getline(file, i.name, ',')
      && (file >> i.itemId).ignore(std::numeric_limits<std::streamsize>::max(), ',')
      && (file >> i.value).ignore(std::numeric_limits<std::streamsize>::max(), ',')
      && (file >> i.max_range).ignore(std::numeric_limits<std::streamsize>::max(), ',')
      && std::getline(file, i.description, ',')
      && std::getline(file, i.rarity, ',')
      && std::getline(file, i.itemType, ',')
      && (file >> i.stat1).ignore(std::numeric_limits<std::streamsize>::max(), ',')
      && (file >> i.stat2).ignore(std::numeric_limits<std::streamsize>::max(), ',')
      && (file >> i.stat3).ignore(std::numeric_limits<std::streamsize>::max(), ',')
      && (file >> i.mod1).ignore(std::numeric_limits<std::streamsize>::max(), ',')
      && (file >> i.mod2).ignore(std::numeric_limits<std::streamsize>::max(), ',')
      && (file >> i.mod3); ) {
    items.push_back(i);
}

    // for testing
    // std::cout << items[1].name << std::endl;
    // std::cout << items[1].itemId << std::endl;
    // std::cout << items[1].value << std::endl;
    // std::cout << items[1].max_range << std::endl;
    // std::cout << items[1].description << std::endl;
    // std::cout << items[1].rarity << std::endl;
    // std::cout << items[1].itemType << std::endl;
    // std::cout << items[1].stat1 << std::endl;
    // std::cout << items[1].stat2 << std::endl;
    // std::cout << items[1].stat3 << std::endl;

    file.close();
    return items;
}

std::vector<Item> ConvertCsvItemToItem(std::vector<CsvItem> input) {
  std::vector<Item> itemVec;
  for (int i = 0; i < input.size(); ++i) {
    Item newItem;

    StatEffect effect1;
    effect1.Stat = Intelligence; // just use Intelligence as a placeholder for initialization since enums.h doesn't contain a "none" type
    effect1.Modifier = 0;
    effect1.Permanent = false;
    StatEffect effect2;
    effect2.Stat = Intelligence;
    effect2.Modifier = 0;
    effect2.Permanent = false;
    StatEffect effect3;
    effect3.Stat = Intelligence;
    effect3.Modifier = 0;
    effect3.Permanent = false;

    std::vector<StatEffect> newStatEffects;
    newStatEffects.push_back(effect1);
    newStatEffects.push_back(effect2);
    newStatEffects.push_back(effect3);

    CsvItem oldItem = input[i];
    newItem.SetName(oldItem.name);
    newItem.SetItemId(oldItem.itemId);
    newItem.SetValue(oldItem.value);
    newItem.SetMaxRange(oldItem.max_range);
    newItem.SetDescription(oldItem.description);
    newItem.SetRarity(oldItem.rarity);
    newItem.SetItemType(oldItem.itemType);

    if (oldItem.stat1 > -1) {
      switch (oldItem.stat1) {
      case 0:
        newItem.SetStat(1, Mana, oldItem.mod1, false);
      case 1:
        newItem.SetStat(1, Health, oldItem.mod1, false);
      case 2:
        newItem.SetStat(1, Intelligence, oldItem.mod1, false);
      case 3:
        newItem.SetStat(1, Strength, oldItem.mod1, false);
      case 4:
        newItem.SetStat(1, Agility, oldItem.mod1, false);
      case 5:
        newItem.SetStat(1, Constitution, oldItem.mod1, false);
      case 6:
        newItem.SetStat(1, Speed, oldItem.mod1, false);
      case 7:
        newItem.SetStat(1, Charisma, oldItem.mod1, false);
      case 8:
        newItem.SetStat(1, Endurance, oldItem.mod1, false);
      case 9:
        newItem.SetStat(1, Attack, oldItem.mod1, false);
      case 10:
        newItem.SetStat(1, Defense, oldItem.mod1, false);
      case 11:
        newItem.SetStat(1, ActionCoolDown, oldItem.mod1, false);  
      case 12:
        newItem.SetStat(1, MagicCoolDown, oldItem.mod1, false);
      }       
    }; 

    if (oldItem.stat2 > -1) {
      switch (oldItem.stat2) {
      case 0:
        newItem.SetStat(2, Mana, oldItem.mod2, false);
      case 1:
        newItem.SetStat(2, Health, oldItem.mod2, false);
      case 2:
        newItem.SetStat(2, Intelligence, oldItem.mod2, false);
      case 3:
        newItem.SetStat(2, Strength, oldItem.mod2, false);
      case 4:
        newItem.SetStat(2, Agility, oldItem.mod2, false);
      case 5:
        newItem.SetStat(2, Constitution, oldItem.mod2, false);
      case 6:
        newItem.SetStat(2, Speed, oldItem.mod2, false);
      case 7:
        newItem.SetStat(2, Charisma, oldItem.mod2, false);
      case 8:
        newItem.SetStat(2, Endurance, oldItem.mod2, false);
      case 9:
        newItem.SetStat(2, Attack, oldItem.mod2, false);
      case 10:
        newItem.SetStat(2, Defense, oldItem.mod2, false);
      case 11:
        newItem.SetStat(2, ActionCoolDown, oldItem.mod2, false);  
      case 12:
        newItem.SetStat(2, MagicCoolDown, oldItem.mod2, false);
      }       
    };

    if (oldItem.stat3 > -1) {
      switch (oldItem.stat3) {
      case 0:
        newItem.SetStat(3, Mana, oldItem.mod3, false);
      case 1:
        newItem.SetStat(3, Health, oldItem.mod3, false);
      case 2:
        newItem.SetStat(3, Intelligence, oldItem.mod3, false);
      case 3:
        newItem.SetStat(3, Strength, oldItem.mod3, false);
      case 4:
        newItem.SetStat(3, Agility, oldItem.mod3, false);
      case 5:
        newItem.SetStat(3, Constitution, oldItem.mod3, false);
      case 6:
        newItem.SetStat(3, Speed, oldItem.mod3, false);
      case 7:
        newItem.SetStat(3, Charisma, oldItem.mod3, false);
      case 8:
        newItem.SetStat(3, Endurance, oldItem.mod3, false);
      case 9:
        newItem.SetStat(3, Attack, oldItem.mod3, false);
      case 10:
        newItem.SetStat(3, Defense, oldItem.mod3, false);
      case 11:
        newItem.SetStat(3, ActionCoolDown, oldItem.mod3, false);  
      case 12:
        newItem.SetStat(3, MagicCoolDown, oldItem.mod3, false);
      }       
    };    

    itemVec.push_back(newItem);
  }

}

// example of how to use these functions:
int main() {
  std::vector<CsvItem> items = GenerateCsvItems();
  std::vector<Item> realItems = ConvertCsvItemToItem(items);
  return 0;
}