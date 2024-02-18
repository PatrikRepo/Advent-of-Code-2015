#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <utility>

struct Place
{
	unsigned int id = 0;
	std::vector<std::pair<unsigned int,unsigned int>> distances;
};

void parseInput(std::unordered_map<unsigned int, Place> &map)
{
	std::string line;
	std::unordered_map<std::string, unsigned int> placeToId;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		unsigned int id = 0;
		while(getline(input,line))
		{
			std::string name;
			size_t pos = 0;
			size_t endpos = 0;
			endpos = line.find_first_of(" ");
			name = line.substr(0,endpos);
			if(placeToId.count(name) == 0)
			{
				placeToId[name] = id;
				map[id] = Place();
				map[id].id = id;
				id++;
			} 
			Place* place = &map[placeToId[name]];
			
			pos = endpos + 4;
			endpos = line.find_first_of(" ", pos);
			
			name = line.substr(pos, endpos - pos);
			
			if(placeToId.count(name) == 0)
			{
				placeToId[name] = id;
				map[id] = Place();
				map[id].id = id;
				id++;
			} 
			Place* dest = &map[placeToId[name]];
			
			pos = endpos + 3;
			unsigned int distance = std::stoi(line.substr(pos));
			
			place->distances.push_back(std::make_pair(dest->id, distance));
			dest->distances.push_back(std::make_pair(place->id, distance));
		}
	}
	input.close();
}

uint64_t shortestDistance(std::unordered_map<unsigned int, Place> &map, const unsigned int from, const unsigned int here, const unsigned int visNum, std::vector<bool> visited)
{
	uint64_t result = 0;

	if(visNum < map.size()-1)
	{
		result = UINT64_MAX;
		visited[here] = true;
		
		uint64_t newResult = 0;		
		for(unsigned int i=0; i<map.size(); i++)
		{
			if(visited[i] == false)
			{
				newResult = shortestDistance(map, here, i, visNum+1, visited);
				if(newResult < result)
				{
					result = newResult;
				}			
			}
		}
	}
	
	Place* fromPlace = &map[from];
	for(auto it=fromPlace->distances.begin(); it!=fromPlace->distances.end(); it++)
	{
		if(here == it->first)
		{
			uint64_t temp = it->second;
			result = result + temp;
			break;
		}
	}
	
	return result;
}

uint64_t shortestDistance(std::unordered_map<unsigned int, Place> &map)
{
	uint64_t result = UINT64_MAX;
	
	std::vector<bool> visited;
	for(unsigned int i=0; i<map.size(); i++)
	{
		visited.push_back(false);
	}
	
	for(unsigned int i=0; i<map.size(); i++)
	{
		visited[i] = true;
		for(unsigned int j=0; j<map.size(); j++)
		{
			if(i!=j)
			{
				uint64_t newResult = shortestDistance(map, i, j, 1, visited);
				if(newResult < result)
				{
					result = newResult;
				}
			}
		}
		visited[i] = false;
	}
	
	return result;
}


uint64_t longestDistance(std::unordered_map<unsigned int, Place> &map, const unsigned int from, const unsigned int here, const unsigned int visNum, std::vector<bool> visited)
{
	uint64_t result = 0;

	if(visNum < map.size()-1)
	{
		visited[here] = true;
		
		uint64_t newResult = 0;		
		for(unsigned int i=0; i<map.size(); i++)
		{
			if(visited[i] == false)
			{
				newResult = longestDistance(map, here, i, visNum+1, visited);
				if(newResult > result)
				{
					result = newResult;
				}			
			}
		}
	}
	
	Place* fromPlace = &map[from];
	for(auto it=fromPlace->distances.begin(); it!=fromPlace->distances.end(); it++)
	{
		if(here == it->first)
		{
			uint64_t temp = it->second;
			result = result + temp;
			break;
		}
	}
	
	return result;
}

uint64_t longestDistance(std::unordered_map<unsigned int, Place> &map)
{
	uint64_t result = 0;
	
	std::vector<bool> visited;
	for(unsigned int i=0; i<map.size(); i++)
	{
		visited.push_back(false);
	}
	
	for(unsigned int i=0; i<map.size(); i++)
	{
		visited[i] = true;
		for(unsigned int j=0; j<map.size(); j++)
		{
			if(i!=j)
			{
				uint64_t newResult = longestDistance(map, i, j, 1, visited);
				if(newResult > result)
				{
					result = newResult;
				}
			}
		}
		visited[i] = false;
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;

	std::unordered_map<unsigned int, Place> map;
	
	parseInput(map);

	resultA = shortestDistance(map);
	resultB = longestDistance(map);
	
	std::cout << "resultA: " << resultA << std::endl;
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
