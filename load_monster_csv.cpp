#include "load_monster_csv.h"
#include <string>
#include <fstream>
#include <sstream>


std::vector<Enemy*> loadMonsterFromFile() {
		std::vector<Enemy*> monsterVector;						//Create vector of dynamically allocated Enemy object
		std::ifstream monsterFile("Enemies.csv");				//Open file
		int numMonster = 0;										//Counter for vector index

		std::string str;
		std::getline(monsterFile, str);
		while (std::getline(monsterFile, str))
		{
			int count = 1;										//counter for switch statement
			monsterVector.push_back(new Enemy());
			std::istringstream iss(str);
			std::string token;
			while (std::getline(iss, token, ','))
			{
				switch (count) {
				case 1://Get name
					monsterVector[numMonster]->set_name(token);					
					count++;
					break;
				case 2://Get intelligence
					monsterVector[numMonster]->AlterStat(Intelligence, true, std::stoi(token));
					count++;
					break;
				case 3://Get Strength
					monsterVector[numMonster]->AlterStat(Strength, true, std::stoi(token));
					count++;
					break;
				case 4://Get Agility
					monsterVector[numMonster]->AlterStat(Agility, true, std::stoi(token));
					count++;
					break;
				case 5://Get Constitution
					monsterVector[numMonster]->AlterStat(Constitution, true, std::stoi(token));
					count++;
					break;
				case 6://Get speed
					monsterVector[numMonster]->AlterStat(Speed, true, std::stoi(token));
					count++;
					break;
				case 7://get Charisma
					monsterVector[numMonster]->AlterStat(Charisma, true, std::stoi(token));
					count++;
					break;
				case 8://get endurance
					monsterVector[numMonster]->AlterStat(Endurance, true, std::stoi(token));
					count++;
					break;
				case 9://get gold
					monsterVector[numMonster]->AlterGold(std::stoi(token));
					numMonster++;
					break;
				}
			}
		}
		return monsterVector;					//return vector
}
