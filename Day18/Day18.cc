#include <iostream>
#include <fstream>
#include <vector>

void parseInput(std::vector<std::string> &map)
{
	std::string line;
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input,line))
		{
			map.push_back(line);
		}
	}
	input.close();
}

int checkNeighbours(const unsigned int x, const unsigned int y, const std::vector<std::string> &referenceMap)
{
	int result = 0;

	for(unsigned int i=(y>0 ? y-1:0); i<(y+1<referenceMap.size() ? y+2:y+1); i++)
	{
		for(unsigned int j=(x>0 ? x-1:0); j<(x+1<referenceMap[0].length() ? x+2:x+1); j++)
		{
			if(referenceMap[i][j] == '#' && !(i == y && j == x))
			{
				result++;
			}
		}
	}
	
	return result;
}

void animateMap(std::vector<std::string> &map, const bool cornersOn)
{
	std::vector<std::string> referenceMap = map;
	
	for(unsigned int i=0; i<map.size(); i++)
	{
		for(unsigned int j=0; j<map[0].length(); j++)
		{
			int neighbours = checkNeighbours(j, i, referenceMap);
			if(map[i][j] == '#' && neighbours != 2 && neighbours != 3)
			{
				if(!cornersOn || !((i == 0 || i == map.size()-1) && (j == 0 || j == map[0].length()-1)))
				{
					map[i][j] = '.';
				}
			}
			else if(map[i][j] == '.' && neighbours == 3)
			{
				map[i][j] = '#';
			}
		}
	}
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::string> map;
	std::vector<std::string> cornersStuckMap;
	parseInput(map);
	cornersStuckMap = map;
	
	for(int i=0; i<100; i++)
	{
		animateMap(map, false);
	}

	for(unsigned int i=0; i<map.size(); i++)
	{
		for(unsigned int j=0; j<map[0].length(); j++)
		{
			if(map[i][j] == '#')
			{
				resultA++;
			}
		}
	}
	
	for(int i=0; i<100; i++)
	{
		animateMap(cornersStuckMap, true);
	}

	for(unsigned int i=0; i<cornersStuckMap.size(); i++)
	{
		for(unsigned int j=0; j<cornersStuckMap[0].length(); j++)
		{
			if(cornersStuckMap[i][j] == '#')
			{
				resultB++;
			}
		}
	}
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
