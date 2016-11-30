#include <sstream>
#include <string>
#include "enums.h"
#include <istream>
#include <iostream>
#include <vector>
#include <limits>
#include <fstream>
#include "item.cpp"

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

    std::cout << items[1].name << std::endl;
    std::cout << items[1].itemId << std::endl;
    std::cout << items[1].value << std::endl;
    std::cout << items[1].max_range << std::endl;
    std::cout << items[1].description << std::endl;
    std::cout << items[1].rarity << std::endl;
    std::cout << items[1].itemType << std::endl;
    std::cout << items[1].stat1 << std::endl;
    std::cout << items[1].stat2 << std::endl;
    std::cout << items[1].stat3 << std::endl;

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

    int StatTable[2][6]; 

    // build stat table

    itemVec.push_back(newItem);
  }

}

// example of how to use these functions:
// int main() {
//   std::vector<CsvItem> items = GenerateCsvItems();
//   std::vector<Item> realItems = ConvertCsvItemToItem(items);
//   return 0;
// }