#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

void parseInput(std::vector<unsigned int> &monster)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			size_t pos = line.find_first_of("1234567890");
			monster.push_back(std::stoi(line.substr(pos)));
		}
	}
	input.close();
}

void setupShop(std::vector<std::pair<unsigned int,unsigned int>> &weapons, std::vector<std::pair<unsigned int,unsigned int>> &armor, std::vector<std::pair<unsigned int,unsigned int>> &rings)
{
	weapons.push_back(std::make_pair(4,8));
	weapons.push_back(std::make_pair(5,10));
	weapons.push_back(std::make_pair(6,25));
	weapons.push_back(std::make_pair(7,40));
	weapons.push_back(std::make_pair(8,74));
	armor.push_back(std::make_pair(1,13));
	armor.push_back(std::make_pair(2,31));
	armor.push_back(std::make_pair(3,53));
	armor.push_back(std::make_pair(4,75));
	armor.push_back(std::make_pair(5,102));
	rings.push_back(std::make_pair(1,25));
	rings.push_back(std::make_pair(2,50));
	rings.push_back(std::make_pair(3,100));
	rings.push_back(std::make_pair(1,20));
	rings.push_back(std::make_pair(2,40));
	rings.push_back(std::make_pair(3,80));
}

uint64_t fightMonster(const std::vector<unsigned int> &monster, const std::vector<std::pair<unsigned int,unsigned int>> &weapons, const std::vector<std::pair<unsigned int,unsigned int>> &armor, const std::vector<std::pair<unsigned int,unsigned int>> &rings)
{
	uint64_t result = UINT64_MAX;
	unsigned int attack = 0;
	unsigned int defence = 0;
	unsigned int ringAttack = 0;
	unsigned int ringDefence = 0;
	unsigned int cost = 0;
	
	for(unsigned int i=0; i<weapons.size(); i++)
	{
		attack = weapons[i].first;
		cost = weapons[i].second;
		
		for(unsigned int j=0; j<=armor.size(); j++)
		{
			if(j<armor.size())
			{
				defence = armor[j].first;
				cost += armor[j].second;
			}
			for(unsigned int k=0; k<=rings.size(); k++)
			{
				if(k<rings.size())
				{
					if(k<3)
					{
						ringAttack = rings[k].first;
					}
					else
					{
						ringDefence = rings[k].first;
					}
					cost += rings[k].second;
				}
				for(unsigned int l=k+1; l<=rings.size(); l++)
				{
					if(l<rings.size())
					{
						if(l<3)
						{
							ringAttack += rings[l].first;
						}
						else
						{
							ringDefence += rings[l].first;
						}
						cost += rings[l].second;
					}

					int heroDamage = attack+ringAttack-monster[2];
					if(heroDamage <= 0)
					{
						heroDamage = 1;
					}
					int monsterDamage = monster[1]-defence-ringDefence;
					if(monsterDamage <= 0)
					{
						monsterDamage = 1;
					}
					int heroCycles = monster[0]/heroDamage;
					if(monster[0]%heroDamage > 0)
					{
						heroCycles++;
					}
					int monsterCycles = 100/monsterDamage;
					if(100%monsterDamage > 0)
					{
						monsterCycles++;
					}

					if(heroCycles <= monsterCycles)
					{
						if(cost<result)
						{
							result = cost;
						}
					}
					
					if(l<rings.size())
					{
						cost -= rings[l].second;
						if(l<3)
						{
							ringAttack -= rings[l].first;
						}
						else if(l<rings.size())
						{
							ringDefence -= rings[l].first;
						}
					}
				}
				if(k<rings.size())
				{
					cost -= rings[k].second;
					ringAttack = 0;
					ringDefence = 0;
				}
			}
			if(j<armor.size())
			{
				cost -= armor[j].second;
				defence = 0;
			}
		}
	}
	
	return result;
}


uint64_t loseToMonster(const std::vector<unsigned int> &monster, const std::vector<std::pair<unsigned int,unsigned int>> &weapons, const std::vector<std::pair<unsigned int,unsigned int>> &armor, const std::vector<std::pair<unsigned int,unsigned int>> &rings)
{
	uint64_t result = 0;
	unsigned int attack = 0;
	unsigned int defence = 0;
	unsigned int ringAttack = 0;
	unsigned int ringDefence = 0;
	unsigned int cost = 0;
	
	for(unsigned int i=0; i<weapons.size(); i++)
	{
		attack = weapons[i].first;
		cost = weapons[i].second;
		
		for(unsigned int j=0; j<=armor.size(); j++)
		{
			if(j<armor.size())
			{
				defence = armor[j].first;
				cost += armor[j].second;
			}
			for(unsigned int k=0; k<=rings.size(); k++)
			{
				if(k<rings.size())
				{
					if(k<3)
					{
						ringAttack = rings[k].first;
					}
					else
					{
						ringDefence = rings[k].first;
					}
					cost += rings[k].second;
				}
				for(unsigned int l=k+1; l<=rings.size(); l++)
				{
					if(l<rings.size())
					{
						if(l<3)
						{
							ringAttack += rings[l].first;
						}
						else
						{
							ringDefence += rings[l].first;
						}
						cost += rings[l].second;
					}

					int heroDamage = attack+ringAttack-monster[2];
					if(heroDamage <= 0)
					{
						heroDamage = 1;
					}
					int monsterDamage = monster[1]-defence-ringDefence;
					if(monsterDamage <= 0)
					{
						monsterDamage = 1;
					}
					int heroCycles = monster[0]/heroDamage;
					if(monster[0]%heroDamage > 0)
					{
						heroCycles++;
					}
					int monsterCycles = 100/monsterDamage;
					if(100%monsterDamage > 0)
					{
						monsterCycles++;
					}

					if(heroCycles > monsterCycles)
					{
						if(cost>result)
						{
							result = cost;
						}
					}
					
					if(l<rings.size())
					{
						cost -= rings[l].second;
						if(l<3)
						{
							ringAttack -= rings[l].first;
						}
						else if(l<rings.size())
						{
							ringDefence -= rings[l].first;
						}
					}
				}
				if(k<rings.size())
				{
					cost -= rings[k].second;
					ringAttack = 0;
					ringDefence = 0;
				}
			}
			if(j<armor.size())
			{
				cost -= armor[j].second;
				defence = 0;
			}
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<unsigned int> monster;
	
	std::vector<std::pair<unsigned int,unsigned int>> weapons;
	std::vector<std::pair<unsigned int,unsigned int>> armor;
	std::vector<std::pair<unsigned int,unsigned int>> rings;
	
	parseInput(monster);
	setupShop(weapons, armor, rings);
	
	resultA = fightMonster(monster, weapons, armor, rings);
	resultB = loseToMonster(monster, weapons, armor, rings);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
