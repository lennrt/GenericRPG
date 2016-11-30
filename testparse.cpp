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
        newItem.AlterStat(Mana, true, oldItem.mod1);
      case 1:
        newItem.AlterStat(Health, true, oldItem.mod1);
      case 2:
        newItem.AlterStat(Intelligence, true, oldItem.mod1);
      case 3:
        newItem.AlterStat(Strength, true, oldItem.mod1);
      case 4:
        newItem.AlterStat(Agility, true, oldItem.mod1);
      case 5:
        newItem.AlterStat(Constitution, true, oldItem.mod1);
      case 6:
        newItem.AlterStat(Speed, true, oldItem.mod1);
      case 7:
        newItem.AlterStat(Charisma, true, oldItem.mod1);
      case 8:
        newItem.AlterStat(Endurance, true, oldItem.mod1);
      case 9:
        newItem.AlterStat(Attack, true, oldItem.mod1);
      case 10:
        newItem.AlterStat(Defense, true, oldItem.mod1);
      case 11:
        newItem.AlterStat(ActionCoolDown, true, oldItem.mod1);  
      case 12:
        newItem.AlterStat(MagicCoolDown, true, oldItem.mod1);
      }       
    }; 

    if (oldItem.stat2 > -1) {
      switch (oldItem.stat2) {
      case 0:
        newItem.AlterStat(Mana, true, oldItem.mod2);
      case 1:
        newItem.AlterStat(Health, true, oldItem.mod2);
      case 2:
        newItem.AlterStat(Intelligence, true, oldItem.mod2);
      case 3:
        newItem.AlterStat(Strength, true, oldItem.mod2);
      case 4:
        newItem.AlterStat(Agility, true, oldItem.mod2);
      case 5:
        newItem.AlterStat(Constitution, true, oldItem.mod2);
      case 6:
        newItem.AlterStat(Speed, true, oldItem.mod2);
      case 7:
        newItem.AlterStat(Charisma, true, oldItem.mod2);
      case 8:
        newItem.AlterStat(Endurance, true, oldItem.mod2);
      case 9:
        newItem.AlterStat(Attack, true, oldItem.mod2);
      case 10:
        newItem.AlterStat(Defense, true, oldItem.mod2);
      case 11:
        newItem.AlterStat(ActionCoolDown, true, oldItem.mod2);  
      case 12:
        newItem.AlterStat(MagicCoolDown, true, oldItem.mod2);
      }       
    };

    if (oldItem.stat3 > -1) {
      switch (oldItem.stat3) {
      case 0:
        newItem.AlterStat(Mana, true, oldItem.mod3);
      case 1:
        newItem.AlterStat(Health, true, oldItem.mod3);
      case 2:
        newItem.AlterStat(Intelligence, true, oldItem.mod3);
      case 3:
        newItem.AlterStat(Strength, true, oldItem.mod3);
      case 4:
        newItem.AlterStat(Agility, true, oldItem.mod3);
      case 5:
        newItem.AlterStat(Constitution, true, oldItem.mod3);
      case 6:
        newItem.AlterStat(Speed, true, oldItem.mod3);
      case 7:
        newItem.AlterStat(Charisma, true, oldItem.mod3);
      case 8:
        newItem.AlterStat(Endurance, true, oldItem.mod3);
      case 9:
        newItem.AlterStat(Attack, true, oldItem.mod3);
      case 10:
        newItem.AlterStat(Defense, true, oldItem.mod3);
      case 11:
        newItem.AlterStat(ActionCoolDown, true, oldItem.mod3);  
      case 12:
        newItem.AlterStat(MagicCoolDown, true, oldItem.mod3);
      }       
    };    

    itemVec.push_back(newItem);
  }

}

// example of how to use these functions:
// int main() {
//   std::vector<CsvItem> items = GenerateCsvItems();
//   std::vector<Item> realItems = ConvertCsvItemToItem(items);
//   return 0;
// }