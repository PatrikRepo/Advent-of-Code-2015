#include <iostream>
#include <fstream>

int64_t sumNumbers(const std::string &line)
{
	int64_t result = 0;
	
	size_t pos = 0;
	size_t endpos = 0;
	pos = line.find_first_of("1234567890");

	while(pos != std::string::npos)
	{
		endpos = line.find_first_not_of("1234567890", pos);
		if(line[pos-1] == '-')
		{
			pos--;
		}
		result += std::stoi(line.substr(pos, endpos-pos));
		pos = line.find_first_of("1234567890", endpos);
	}
	
	return result;
}

void removeReds(std::string &line)
{
	std::string result;
	size_t pos = 0;
	
	pos = line.find_first_of("r");
	while(pos != std::string::npos)
	{
		if(line[pos-2] == ':')
		{
			int count = 0;
			size_t startPos = pos;
			size_t endPos = pos;
			while(line[startPos] != '{' || count != 0)
			{
				if(line[startPos] == '}')
				{
					count++;
				}
				else if(line[startPos] == '{')
				{
					count--;
				}
				startPos--;
			}
			while(line[endPos] != '}' || count != 0)
			{
				if(line[endPos] == '{')
				{
					count++;
				}
				else if(line[endPos] == '}')
				{
					count--;
				}
				endPos++;
			}
			line.erase(startPos, endPos-startPos+1);
			pos = startPos;
		}
		pos = line.find_first_of("r", pos+1);
	}
}

int main()
{
	int64_t resultA = 0;
	int64_t resultB = 0;
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input,line);
	}
	input.close();
	
	resultA = sumNumbers(line);
	
	removeReds(line);
	resultB = sumNumbers(line);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
