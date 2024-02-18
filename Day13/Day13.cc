#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>

struct Guest
{
	std::vector<std::pair<int,int>> happiness;
};

void parseInput(std::vector<Guest> &guests)
{
	std::string line;
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		int id = 0;
		std::unordered_map<std::string,int> idMap;
		while(getline(input,line))
		{
			size_t pos = 0;
			size_t endpos = 0;
			
			endpos = line.find_first_of(" ");
			std::string name = line.substr(0, endpos);
			
			if(idMap.count(name) == 0)
			{
				idMap[name] = id;
				id++;
				guests.push_back(Guest());
			}
			
			endpos = line.find_first_of(" ", endpos+1);
			pos = endpos+1;
			endpos = line.find_first_of(" ", pos);
			
			char direction = line[pos];

			pos = endpos+1;
			endpos = line.find_first_of(" ", pos);
			
			int happiness = std::stoi(line.substr(pos, endpos-pos));
			if(direction == 'l')
			{
				happiness = -happiness;
			}
			
			pos = line.find_last_of(" ") +1;
			
			std::string neighbourName = line.substr(pos, line.length()-pos-1);
			
			if(idMap.count(neighbourName) == 0)
			{
				idMap[neighbourName] = id;
				id++;
				guests.push_back(Guest());
			}
			
			guests[idMap[name]].happiness.push_back(std::make_pair(idMap[neighbourName],happiness));
		}
	}
	input.close();
}

void addSelf(std::vector<Guest> &guests)
{
	int meId = guests.size();
	for(auto it=guests.begin(); it!=guests.end(); it++)
	{
		it->happiness.push_back(std::make_pair(meId,0));
	}
	
	Guest me;
	for(int i=0; i<meId; i++)
	{
		me.happiness.push_back(std::make_pair(i,0));
	}
	guests.push_back(me);
}

int64_t calculateHappiness(std::vector<Guest> &guests, const int first, const int from, const int here, const unsigned int placedNum, std::vector<bool> placed)
{
	int64_t result = 0;

	if(placedNum < guests.size()-1)
	{
		placed[here] = true;
		
		int64_t newResult = INT64_MIN;		
		for(unsigned int i=0; i<guests.size(); i++)
		{
			if(placed[i] == false)
			{
				newResult = calculateHappiness(guests, first, here, i, placedNum+1, placed);
				if(newResult > result)
				{
					result = newResult;
				}			
			}
		}
	}
	else
	{
		Guest* guest = &guests[first];
		for(auto it=guest->happiness.begin(); it!=guest->happiness.end(); it++)
		{
			if(here == it->first)
			{
				result += it->second;
				break;
			}
		}
		
		guest = &guests[here];
		for(auto it=guest->happiness.begin(); it!=guest->happiness.end(); it++)
		{
			if(first == it->first)
			{
				result += it->second;
				break;
			}
		}
	}
	
	Guest* guest = &guests[from];
	for(auto it=guest->happiness.begin(); it!=guest->happiness.end(); it++)
	{
		if(here == it->first)
		{
			result += it->second;
			break;
		}
	}
	
	guest = &guests[here];
	for(auto it=guest->happiness.begin(); it!=guest->happiness.end(); it++)
	{
		if(from == it->first)
		{
			result += it->second;
			break;
		}
	}
	
	return result;
}

int64_t calculateHappiness(std::vector<Guest> &guests)
{
	int64_t result = INT64_MIN;
	
	std::vector<bool> placed;
	for(unsigned int i=0; i<guests.size(); i++)
	{
		placed.push_back(false);
	}
	
	for(unsigned int i=0; i<guests.size(); i++)
	{
		placed[i] = true;
		for(unsigned int j=0; j<guests.size(); j++)
		{
			if(i!=j)
			{
				int64_t newResult = calculateHappiness(guests, i, i, j, 1, placed);
				if(newResult > result)
				{
					result = newResult;
				}
			}
		}
		placed[i] = false;
	}
	
	return result;
}

int main()
{
	int64_t resultA = 0;
	int64_t resultB = 0;
	std::vector<Guest> guests;
	
	parseInput(guests);
	
	resultA = calculateHappiness(guests);
	
	addSelf(guests);
	resultB = calculateHappiness(guests);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
