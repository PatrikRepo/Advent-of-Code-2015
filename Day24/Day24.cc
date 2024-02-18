#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

void parseInput(std::vector<int> &numbers)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input,line))
		{
			numbers.push_back(std::stoi(line));
		}
	}
	input.close();
}

int sumOfSet(const std::vector<int> &set)
{
	int result = 0;
	for(unsigned int i=0; i<set.size(); i++)
	{
		result += set[i];
	}
	return result;
}

bool splitIntoGroups(std::vector<int> &numbers, const int totalSum, const int index, std::vector<std::vector<int>> subSets)
{
	bool result = false;
	if(index >= 0)
	{
	
				result = true;
			for(unsigned int i=0; i<subSets.size()-1; i++)
			{
				if(sumOfSet(subSets[i]) != totalSum)
				{
					result = false;
				}
			}
		
		if(!result)
		{
			for(unsigned int i=0; i<subSets.size(); i++)
			{
				if(sumOfSet(subSets[i]) + numbers[index] <= totalSum)
				{
					(subSets[i]).push_back(numbers[index]);
					bool newResult = splitIntoGroups(numbers, totalSum, index-1, subSets);
					if(newResult)
					{
						result = newResult;
						break;
					}
					subSets[i].pop_back();
				}
			}
		}
	}

	return result;
}

bool splitable(std::vector<int> &numbers, const int totalSum, const int numberOfGroups)
{
	bool result = false;
	
	std::vector<std::vector<int>> subSets;
	std::vector<int> subSet;
	for(int i=0; i<numberOfGroups-1; i++)
	{
		subSets.push_back(subSet);
	}
	
	result = splitIntoGroups(numbers, totalSum, numbers.size()-1, subSets);
	
	return result;
}

std::pair<int, uint64_t> split(std::vector<int> numbers, std::vector<int> subSet, const int index, const int sum, const int totalSum, const int numberOfGroups, unsigned int &lowest)
{
	std::pair<int, uint64_t> result = std::make_pair(numbers.size(), UINT64_MAX);

	if(index>=0)
	{
		if(sum - numbers[index] >= 0 && subSet.size() < lowest)
		{
			subSet.push_back(numbers[index]);
			auto newNumbers = numbers;
			newNumbers.erase(newNumbers.begin()+index);
			if(sum - subSet.back() > 0)
			{
				result = split(newNumbers, subSet, index-1, sum-subSet.back(), totalSum, numberOfGroups, lowest);
			}
			else if(sum - subSet.back() == 0 && splitable(newNumbers, totalSum, numberOfGroups))
			{
				result.first = subSet.size();
				lowest = result.first;
				result.second = 1;
				for(unsigned int i=0; i<subSet.size(); i++)
				{
					result.second *= subSet[i];
				}
			}
			subSet.pop_back();
		}
		auto newResult = split(numbers, subSet, index-1, sum, totalSum, numberOfGroups, lowest);
		if(newResult.first < result.first || (newResult.first == result.first && newResult.second < result.second))
		{
			result = newResult;
		}
	}
	return result;
}

uint64_t split(std::vector<int> &numbers, const int numberOfGroups)
{
	uint64_t result = 0;
	std::vector<int> subset;
	std::unordered_map<uint64_t,std::pair<int,uint64_t>> cache;
	
	int sum = 0;
	for(unsigned int i=0; i<numbers.size(); i++)
	{
		sum += numbers[i];
	}
	sum /= numberOfGroups;
	unsigned int size = numbers.size();
	auto pair = split(numbers, subset, size-1, sum, sum, numberOfGroups, size);
	result = pair.second;
	
	return result;
}

int main()
{
	uint64_t result = 0;
	std::vector<int> numbers;
	
	parseInput(numbers);
	
	result = split(numbers, 3);
	
	std::cout << "result A: " << result << std::endl;
	
	result = split(numbers, 4);
	
	std::cout << "result B: " << result << std::endl;
	return 0;
}
