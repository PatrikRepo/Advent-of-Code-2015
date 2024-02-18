#include <iostream>
#include <fstream>
#include <vector>

void parseInput(std::vector<int> &monster)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input,line))
		{
			size_t pos = line.find_first_of("1234567890");
			monster.push_back(std::stoi(line.substr(pos)));
		}
	}
	input.close();
}

uint64_t fightMonster(const std::vector<int> &monster)
{
	uint64_t result = 0;
	bool done = false;
	int shields = 0;
	
	while(!done)
	{
		int manaCost = 0;
		int manaMax = 500;
		
		bool poisonUp = false;
		int poisonCounter = 0;
		
		bool rechargeUp = false;
		int rechargeCounter = 0;
		
		bool shieldUp = false;
		int shieldCounter = 0;
		
		int heroHP = 50;
		int monsterHP = monster[0];
		int heroDefence = 0;
		int monsterAttack = monster[1];
		
		while(heroHP > 0)
		{
			if(poisonUp)
			{
				monsterHP -= 3;
				poisonCounter--;
				if(poisonCounter == 0)
				{
					poisonUp = false;
				}
			}
			if(rechargeUp)
			{
				manaMax += 101;
				rechargeCounter--;
				if(rechargeCounter == 0)
				{
					rechargeUp = false;
				}
			}
			if(shieldUp)
			{
				shieldCounter--;
				if(shieldCounter == 0)
				{
					heroDefence = 0;
					shieldUp = false;
				}
			}
			if(monsterHP <= 0)
			{
				done = true;
				break;
			}
			if(monsterHP <= 4 || (monsterHP <= 7 && poisonUp))
			{
				manaCost += 53;
				monsterHP -= 4;
			}
			else if(heroHP - (monsterAttack - heroDefence) == -1)
			{
				manaCost += 73;
				monsterHP -= 2;
				heroHP += 2;
			}
			else if(!poisonUp)
			{
				manaCost += 173;
				poisonUp = true;
				poisonCounter = 6;
			}
			else if(!rechargeUp)
			{
				manaCost += 229;
				rechargeUp = true;
				rechargeCounter = 5;
			}
			else if(shields > 0 && !shieldUp)
			{
				shields--;
				manaCost += 113;
				shieldUp = true;
				shieldCounter = 6;
				heroDefence = 7;
			}
			else
			{
				manaCost += 53;
				monsterHP -= 4;
			}
			
			if(poisonUp)
			{
				monsterHP -= 3;
				poisonCounter--;
				if(poisonCounter == 0)
				{
					poisonUp = false;
				}
			}
			if(rechargeUp)
			{
				manaMax += 101;
				rechargeCounter--;
				if(rechargeCounter == 0)
				{
					rechargeUp = false;
				}
			}
			if(shieldUp)
			{
				shieldCounter--;
				if(shieldCounter == 0)
				{
					heroDefence = 0;
					shieldUp = false;
				}
			}
			if(monsterHP <= 0)
			{
				done = true;
				break;
			}
			
			heroHP -= monsterAttack - heroDefence;
		}
		
		if(done)
		{
			result = manaCost;
		}
		else
		{
			shields++;
		}
		
	}
		
	return result;
}

uint64_t fightHardMonster(const std::vector<int> &monster)
{
	uint64_t result = 0;
	bool done = false;
	int shields = 0;
	
	while(!done)
	{
		int manaCost = 0;
		int manaMax = 500;
		
		bool poisonUp = false;
		int poisonCounter = 0;
		
		bool rechargeUp = false;
		int rechargeCounter = 0;
		int numberOfRecharges = 2;
		
		bool shieldUp = false;
		int shieldCounter = 0;
		int usedShields = 0;
		
		int heroHP = 50;
		int monsterHP = monster[0];
		int heroDefence = 0;
		int monsterAttack = monster[1];
		
		while(heroHP > 1)
		{
			heroHP--;
			
			if(poisonUp)
			{
				monsterHP -= 3;
				poisonCounter--;
				if(poisonCounter == 0)
				{
					poisonUp = false;
				}
			}
			if(rechargeUp)
			{
				manaMax += 101;
				rechargeCounter--;
				if(rechargeCounter == 0)
				{
					rechargeUp = false;
				}
			}
			if(shieldUp)
			{
				shieldCounter--;
				if(shieldCounter == 0)
				{
					heroDefence = 0;
					shieldUp = false;
				}
			}
			if(monsterHP <= 0)
			{
				done = true;
				break;
			}
			if(monsterHP <= 4 || (monsterHP <= 7 && poisonUp))
			{
				manaCost += 53;
				monsterHP -= 4;
			}
			else if(heroHP - (monsterAttack - heroDefence) == -1)
			{
				manaCost += 73;
				monsterHP -= 2;
				heroHP += 2;
			}
			else if(!poisonUp)
			{
				manaCost += 173;
				poisonUp = true;
				poisonCounter = 6;
			}
			else if(numberOfRecharges > 0 && !rechargeUp)
			{
				numberOfRecharges--;
				manaCost += 229;
				rechargeUp = true;
				rechargeCounter = 5;
			}
			else if(shields - usedShields> 0 && !shieldUp)
			{
				usedShields++;
				manaCost += 113;
				shieldUp = true;
				shieldCounter = 6;
				heroDefence = 7;
			}
			else
			{
				manaCost += 53;
				monsterHP -= 4;
			}
			
			if(poisonUp)
			{
				monsterHP -= 3;
				poisonCounter--;
				if(poisonCounter == 0)
				{
					poisonUp = false;
				}
			}
			if(rechargeUp)
			{
				manaMax += 101;
				rechargeCounter--;
				if(rechargeCounter == 0)
				{
					rechargeUp = false;
				}
			}
			if(shieldUp)
			{
				shieldCounter--;
				if(shieldCounter == 0)
				{
					heroDefence = 0;
					shieldUp = false;
				}
			}
			if(monsterHP <= 0)
			{
				done = true;
				break;
			}
			
			heroHP -= monsterAttack - heroDefence;
		}
		
		if(done)
		{
			result = manaCost;
		}
		else
		{
			shields++;
		}
		
	}
		
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<int> monster;
	
	parseInput(monster);
	
	resultA = fightMonster(monster);
	resultB = fightHardMonster(monster);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	return 0;
}
