#include <iostream>
#include <fstream>
#include <unordered_map>
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

uint64_t naughtyOrNice(const std::string &line)
{
	uint64_t result = 0;
	int lineLength = line.length();
	int wovels = 0;
	bool dubs = false;
	bool forbidden = false;
	
	for(int i=0; i<lineLength; i++)
	{
		char current = line[i];
		
		if(current == 'a' || current == 'e' || current == 'i' || current == 'o' || current == 'u')
		{
			wovels++;
		}
		if(!dubs && i+1 < lineLength && current == line[i+1])
		{
			dubs = true;
		}
		if(current == 'a' && i+1 < lineLength && line[i+1] == 'b')
		{
			forbidden = true;
			break;
		}
		if(current == 'c' && i+1 < lineLength && line[i+1] == 'd')
		{
			forbidden = true;
			break;
		}
		if(current == 'p' && i+1 < lineLength && line[i+1] == 'q')
		{
			forbidden = true;
			break;
		}
		if(current == 'x' && i+1 < lineLength && line[i+1] == 'y')
		{
			forbidden = true;
			break;
		}
	}
	
	if(!forbidden && wovels >= 3 && dubs)
	{
		result = 1;
	}
	
	return result;
}

uint64_t newNaughtyOrNice(const std::string &line)
{
	uint64_t result = 0;
	std::unordered_map<std::string,int> dubs;
	bool repeat = false;
	int lineLength = line.length();
	
	for(int i=0; i<lineLength-2; i=i+2)
	{
		if(line[i] == line[i+2])
		{
			repeat = true;
			break;
		}
	}
	if(!repeat)
	{
		for(int i=1; i<lineLength-2; i=i+2)
		{
			if(line[i] == line[i+2])
			{
				repeat = true;
				break;
			}
		}
	}
	if(repeat)
	{
		for(int i=0; i<lineLength-1; i++)
		{
			std::string temp = line.substr(i,2);
			dubs[temp] += 1;
			if(line[i] == line[i+1] && i+2 < lineLength && line[i] == line[i+2])
			{
				i++;
			}
		}
		for(auto it=dubs.begin(); it!=dubs.end(); it++)
		{
			if(it->second > 1)
			{
				result++;
				break;
			}
		}
	}
	
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::string> map;
	
	parseInput(map);
	
	for(unsigned int i=0; i<map.size(); i++)
	{
		resultA += naughtyOrNice(map[i]);
		resultB += newNaughtyOrNice(map[i]);
	}
	
	std::cout << "resultA: " << resultA << std::endl;
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
