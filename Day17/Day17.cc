#include <iostream>
#include <fstream>
#include <vector>

void parseInput(std::vector<int> &containers)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input,line))
		{
			containers.push_back(std::stoi(line));
		}
	}
	input.close();
}

uint64_t calculateCombinations(const std::vector<int> &containers, const unsigned int container, const unsigned int sum)
{
	uint64_t result = 0;
	
	if(container+1 < containers.size())
	{
		result += calculateCombinations(containers, container+1, sum);
	}
	
	int newSum = sum-containers[container];
	if(newSum == 0)
	{
		result +=1;
	}
	else if(newSum > 0 && container+1 < containers.size())
	{
		result += calculateCombinations(containers, container+1, newSum);
	}
	
	return result;
}

void calculateMinimumCombinations(const std::vector<int> &containers, unsigned int container, const unsigned int sum, unsigned int &min, unsigned int count, uint64_t &result)
{
	if(container+1 < containers.size())
	{
		calculateMinimumCombinations(containers, container+1, sum, min, count, result);
	}
	
	int newSum = sum-containers[container];
	if(newSum == 0)
	{
		if(count == min)
		{
			result +=1;
		}
		else if(count < min)
		{
			min = count;
			result = 1;
		}
	}
	else if(newSum > 0 && container+1 < containers.size())
	{
		count++;
		calculateMinimumCombinations(containers, container+1, newSum, min, count, result);
	}
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<int> containers;
	
	parseInput(containers);
	
	resultA = calculateCombinations(containers, 0, 150);
	
	unsigned int min = containers.size();
	calculateMinimumCombinations(containers, 0, 150, min, 0, resultB);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
