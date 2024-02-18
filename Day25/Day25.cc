#include <iostream>
#include <fstream>

void parseInput(uint64_t &row, uint64_t &column)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input,line);
		size_t pos = line.find_first_of("1234567890");
		size_t endpos = line.find_first_of(",", pos);
		row = std::stoi(line.substr(pos, endpos-pos));
		
		pos = line.find_first_of("1234567890", endpos);
		endpos = line.find_first_of(".", pos);
		column = std::stoi(line.substr(pos, endpos-pos));
	}
	input.close();
}

int main()
{
	uint64_t result = 0;
	uint64_t row = 0;
	uint64_t column = 0;
	
	parseInput(row, column);
	
	uint64_t count = 0;
	
	for(unsigned int i=2; i<row+column-1; i++)
	{
		count += i;
	}
	count += column;
	
	result = 20151125;
	
	for(unsigned int i=0; i<count; i++)
	{
		result = (result*252533) % 33554393;
	}
	
	std::cout << "result: " << result << std::endl;
	return 0;
}
