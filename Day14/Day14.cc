#include <iostream>
#include <fstream>
#include <vector>

struct Reindeer
{
	unsigned int speed = 0;
	unsigned int active = 0;
	unsigned int cycle = 0;
	std::string name;
	unsigned int points = 0;
	unsigned int dist = 0;
	Reindeer(unsigned int s, unsigned int a, unsigned int c, std::string &n) : speed(s), active(a), cycle(c), name(n) {}
};

void parseInput(std::vector<Reindeer> &reindeers)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input,line))
		{
			size_t pos = 0;
			size_t endpos = line.find_first_of(" ");
			
			std::string name = line.substr(0,endpos);
			
			pos = line.find_first_of("1234567890", endpos);
			endpos = line.find_first_of(" ", pos);
			
			unsigned int speed = std::stoi(line.substr(pos, endpos-pos));
			
			pos = line.find_first_of("1234567890", endpos);
			endpos = line.find_first_of(" ", pos);
			
			unsigned int active = std::stoi(line.substr(pos, endpos-pos));
			
			pos = line.find_first_of("1234567890", endpos);
			endpos = line.find_first_of(" ", pos);
			
			unsigned int cycle  = active + std::stoi(line.substr(pos, endpos-pos));
			
			reindeers.push_back(Reindeer(speed, active, cycle, name));
		}
	}
	input.close();
}

uint64_t maxDistance(std::vector<Reindeer> &reindeers)
{
	uint64_t result = 0;
	
	for(auto it=reindeers.begin(); it!=reindeers.end(); it++)
	{
		uint64_t newResult = 0;
		
		int cycles = 2503/(it->cycle);
		newResult = cycles*((it->active)*(it->speed));
		
		int lastCycle = it->active < 2503%(it->cycle) ? it->active : 2503%(it->cycle);
		newResult += lastCycle*(it->speed);
		
		if(result < newResult)
		{
			result = newResult;
		}
	}
	
	return result;
}

uint64_t maxPoint(std::vector<Reindeer> &reindeers)
{
	uint64_t result = 0;
	
	for(int i=0; i<2503; i++)
	{
		unsigned int maxDist = 0;
		for(auto it=reindeers.begin(); it!=reindeers.end(); it++)
		{
			if(i%(it->cycle) < it->active)
			{
				it->dist += it->speed;
			}
			if(it->dist > maxDist)
			{
				maxDist = it->dist;
			}
		}
		for(auto it=reindeers.begin(); it!=reindeers.end(); it++)
		{
			if(it->dist == maxDist)
			{
				it->points += 1;
			}
		}
	}
	
	for(auto it=reindeers.begin(); it!=reindeers.end(); it++)
	{
		if(result < it->points)
		{
			result = it->points;
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<Reindeer> reindeers;
	
	parseInput(reindeers);
	
	resultA = maxDistance(reindeers);
	resultB = maxPoint(reindeers);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
