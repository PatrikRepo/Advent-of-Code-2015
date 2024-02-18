#include <iostream>
#include <fstream>
#include <vector>

void parseInput(std::vector<std::string> &sues)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input,line))
		{
			sues.push_back(line);
		}
	}
	input.close();
}

uint64_t findSue(const std::vector<std::string> &sues)
{
	uint64_t result = 0;
	
	int children = 3;
	int cats = 7;
	int samoyeds = 2;
	int pomeranians = 3;
	int akitas = 0;
	int vizslas = 0;
	int goldfish = 5;
	int trees = 3;
	int cars = 2;
	int perfumes = 1;
	
	int sue = 1;
	for(unsigned int i=0; i<sues.size(); i++)
	{
		bool done = false;
		size_t pos = sues[i].find_first_of(":") + 1;
		size_t endpos = 0;
		while(pos != std::string::npos)
		{
			done = true;
			pos++;
			endpos = sues[i].find_first_of(":", pos);
			std::string item = sues[i].substr(pos, endpos-pos);
			
			pos = endpos+2;
			endpos = sues[i].find_first_of(",", pos);
			int num = std::stoi(sues[i].substr(pos, endpos-pos));
			
			if(item == "children" && num != children)
			{
				done = false;
			}
			if(item == "cats" && num != cats)
			{
				done = false;
			}
			if(item == "samoyeds" && num != samoyeds)
			{
				done = false;
			}
			if(item == "pomeranians" && num != pomeranians)
			{
				done = false;
			}
			if(item == "akitas" && num != akitas)
			{
				done = false;
			}
			if(item == "vizslas" && num != vizslas)
			{
				done = false;
			}
			if(item == "goldfish" && num != goldfish)
			{
				done = false;
			}
			if(item == "trees" && num != trees)
			{
				done = false;
			}
			if(item == "cars" && num != cars)
			{
				done = false;
			}
			if(item == "perfumes" && num != perfumes)
			{
				done = false;
			}
			if(!done)
			{
				break;
			}
			pos = sues[i].find_first_of(" ", endpos);
		}
		if(done)
		{
			break;
		}
		sue++;
	}
	result = sue;

	return result;
}


uint64_t findRealSue(const std::vector<std::string> &sues)
{
	uint64_t result = 0;
	
	int children = 3;
	int cats = 7;
	int samoyeds = 2;
	int pomeranians = 3;
	int akitas = 0;
	int vizslas = 0;
	int goldfish = 5;
	int trees = 3;
	int cars = 2;
	int perfumes = 1;
	
	int sue = 1;
	for(unsigned int i=0; i<sues.size(); i++)
	{
		bool done = false;
		size_t pos = sues[i].find_first_of(":") + 1;
		size_t endpos = 0;
		while(pos != std::string::npos)
		{
			done = true;
			pos++;
			endpos = sues[i].find_first_of(":", pos);
			std::string item = sues[i].substr(pos, endpos-pos);
			
			pos = endpos+2;
			endpos = sues[i].find_first_of(",", pos);
			int num = std::stoi(sues[i].substr(pos, endpos-pos));
			
			if(item == "children" && num != children)
			{
				done = false;
			}
			if(item == "cats" && num <= cats)
			{
				done = false;
			}
			if(item == "samoyeds" && num != samoyeds)
			{
				done = false;
			}
			if(item == "pomeranians" && num >= pomeranians)
			{
				done = false;
			}
			if(item == "akitas" && num != akitas)
			{
				done = false;
			}
			if(item == "vizslas" && num != vizslas)
			{
				done = false;
			}
			if(item == "goldfish" && num >= goldfish)
			{
				done = false;
			}
			if(item == "trees" && num <= trees)
			{
				done = false;
			}
			if(item == "cars" && num != cars)
			{
				done = false;
			}
			if(item == "perfumes" && num != perfumes)
			{
				done = false;
			}
			if(!done)
			{
				break;
			}
			pos = sues[i].find_first_of(" ", endpos);
		}
		if(done)
		{
			break;
		}
		sue++;
	}
	result = sue;

	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	std::vector<std::string> sues;
	
	parseInput(sues);
	
	resultA = findSue(sues);
	resultB = findRealSue(sues);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
