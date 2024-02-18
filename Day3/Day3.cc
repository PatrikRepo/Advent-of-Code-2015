#include <iostream>
#include <fstream>
#include <utility>
#include <unordered_map>

struct coordinate_Hash {
    std::size_t operator () (const std::pair<int,int> &p) const {
        auto h1 = std::hash<int>{}(p.first);
        auto h2 = std::hash<int>{}(p.second);
        return h1 ^ h2;  
    }
};

void parseInput(std::string &instructions)
{
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input,instructions);
	}
	input.close();
}

void deliver(int &x, int &y, std::unordered_map<std::pair<int,int>, int, coordinate_Hash> &deliveryHashMap, const char direction)
{
	if(direction == '<')
	{
		x--;
	}
	if(direction == '>')
	{
		x++;
	}
	if(direction == 'v')
	{
		y++;
	}
	if(direction == '^')
	{
		y--;
	}
	std::pair<int,int> coordinates(x,y);
	deliveryHashMap[coordinates] += 1;
}

uint64_t deliverAlone(const std::string &instructions)
{
	uint64_t result = 0;
	int x = 0;
	int y = 0;
	std::unordered_map<std::pair<int,int>, int, coordinate_Hash> deliveryHashMap;
	
	deliveryHashMap[std::make_pair(0,0)] += 1;
	for(unsigned int i=0; i<instructions.length(); i++)
	{
		deliver(x,y,deliveryHashMap,instructions[i]);
	}

	result = deliveryHashMap.size();
	
	return result;
}

uint64_t deliveryWithRobot(const std::string &instructions)
{
	uint64_t result = 0;
	int x = 0;
	int y = 0;
	int x2 = 0;
	int y2 = 0;
	std::unordered_map<std::pair<int,int>, int, coordinate_Hash> deliveryHashMap;
	
	deliveryHashMap[std::make_pair(0,0)] += 2;
	for(unsigned int i=0; i<instructions.length(); i++)
	{
		if(i%2 == 0)
		{
			deliver(x,y,deliveryHashMap,instructions[i]);
		}
		else
		{
			deliver(x2,y2,deliveryHashMap,instructions[i]);
		}
	}

	result = deliveryHashMap.size();
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::string instructions;

	parseInput(instructions);
	
	resultA = deliverAlone(instructions);
	resultB = deliveryWithRobot(instructions);
	
	std::cout << "resultA: " << resultA << std::endl;
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
