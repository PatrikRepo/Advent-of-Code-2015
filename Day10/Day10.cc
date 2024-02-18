#include <iostream>
#include <fstream>


std::string lookAndSee(std::string &line)
{
	std::string result;
	int number = 0;
	
	for(unsigned int i=0; i<line.length(); i++)
	{
		number = line[i] - '0';
		int same = 1;
		for(unsigned int j=i+1; j<line.length(); j++)
		{
			if(line[j] == line[i])
			{
				same++;
			}
			else
			{
				break;
			}
		}
		i += (same-1);
		
		number += (same*10);
		result += std::to_string(number);
	}

	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input,line);
	}
	input.close();
	
	for(int i=0; i<40; i++)
	{
		line = lookAndSee(line);
	}
	
	resultA = line.length();
	
	for(int i=0; i<10; i++)
	{
		line = lookAndSee(line);
	}
	
	resultB = line.length();
	
	std::cout << "resultA: " << resultA << std::endl;
	std::cout << "resultB: " << resultB << std::endl;
	return 0;
}
