#include <iostream>
#include <fstream>
#include <vector>

void parseInput(std::vector<std::string> &instructions)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input, line))
		{
			instructions.push_back(line);
		}
	}
	input.close();
}

uint64_t followInstructions(const std::vector<std::string> &instructions)
{
	uint64_t result = 0;
	int map[1000][1000];
	for(int i=0; i<1000; i++)
	{
		for(int j=0; j<1000; j++)
		{
			map[j][i] = 0;
		}
	}
	
	for(auto it=instructions.begin(); it!=instructions.end(); it++)
	{
		int startX = 0;
		int startY = 0;
		int endX = 0;
		int endY = 0;
		size_t pos = 0;
		size_t endpos = 0;
		
		pos = (*it).find_first_of("0123456789");
		endpos = (*it).find_first_of(",");
		startX = std::stoi((*it).substr(pos, endpos-pos));
		
		pos = endpos+1;
		endpos = (*it).find_first_of(" ", pos);
		startY = std::stoi((*it).substr(pos, endpos-pos));
		
		pos = (*it).find_first_of("0123456789", endpos);
		endpos = (*it).find_first_of(",", pos);
		endX = std::stoi((*it).substr(pos, endpos-pos));
		
		pos = endpos+1;
		endY = std::stoi((*it).substr(pos));
		
		for(int i=startX; i<=endX; i++)
		{
			for(int j=startY; j<=endY; j++)
			{
				if((*it)[1] == 'o')
				{
					map[j][i] = (map[j][i]+1)%2;
				}
				else if((*it)[6] == 'f')
				{
					map[j][i] = 0;
				}
				else
				{
					map[j][i] = 1;
				}
			}
		}
	}
		
	for(int i=0; i<1000; i++)
	{
		for(int j=0; j<1000; j++)
		{
			if(map[j][i] == 1)
			{
				result++;
			}
		}
	}
	return result;
}

uint64_t followIndividualInstructions(const std::vector<std::string> &instructions)
{
	uint64_t result = 0;
	int map[1000][1000];
	for(int i=0; i<1000; i++)
	{
		for(int j=0; j<1000; j++)
		{
			map[j][i] = 0;
		}
	}
	
	for(auto it=instructions.begin(); it!=instructions.end(); it++)
	{
		int startX = 0;
		int startY = 0;
		int endX = 0;
		int endY = 0;
		size_t pos = 0;
		size_t endpos = 0;
		
		pos = (*it).find_first_of("0123456789");
		endpos = (*it).find_first_of(",");
		startX = std::stoi((*it).substr(pos, endpos-pos));
		
		pos = endpos+1;
		endpos = (*it).find_first_of(" ", pos);
		startY = std::stoi((*it).substr(pos, endpos-pos));
		
		pos = (*it).find_first_of("0123456789", endpos);
		endpos = (*it).find_first_of(",", pos);
		endX = std::stoi((*it).substr(pos, endpos-pos));
		
		pos = endpos+1;
		endY = std::stoi((*it).substr(pos));
		
		for(int i=startX; i<=endX; i++)
		{
			for(int j=startY; j<=endY; j++)
			{
				if((*it)[1] == 'o')
				{
					map[j][i] += 2;
				}
				else if((*it)[6] == 'f')
				{
					map[j][i] = (map[j][i] == 0 ? 0 : map[j][i]-1);
				}
				else
				{
					map[j][i] += 1;
				}
			}
		}
	}
	
	for(int i=0; i<1000; i++)
	{
		for(int j=0; j<1000; j++)
		{
			result += map[j][i];
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;

	std::vector<std::string> instructions;
	
	parseInput(instructions);
	
	resultA = followInstructions(instructions);
	resultB = followIndividualInstructions(instructions);
	
	
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
