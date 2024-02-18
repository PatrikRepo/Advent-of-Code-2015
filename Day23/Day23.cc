#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

void parseInput(std::vector<std::tuple<std::string, char, int>> &instructions)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input,line))
		{
			size_t pos = line.find_first_of(" ");
			std::string instruction = line.substr(0,pos);
			pos++;
			char r = 0;
			if(line[pos] == 'a' || line[pos] == 'b')
			{
				r = line[pos];
			}
			pos = line.find_first_of("1234567890", pos);
			int value = 0;
			if(pos != std::string::npos)
			{
				if(line[pos-1] == '-')
				{
					pos--;
				}
				value = std::stoi(line.substr(pos));
			}
			instructions.push_back(std::make_tuple(instruction, r, value));
		}
	}
	input.close();
}

void executeInstructions(const std::vector<std::tuple<std::string, char, int>> &instructions, uint64_t &r_a, uint64_t &r_b)
{
	for(unsigned int i=0; i<instructions.size() && i>= 0; i++)
	{
		std::string instruction = std::get<0>(instructions[i]);
		
		if(instruction == "hlf")
		{
			if(std::get<1>(instructions[i]) == 'a')
			{
				r_a /= 2;
			}
			else
			{
				r_b /= 2;
			}
		}
		else if(instruction == "tpl")
		{
			if(std::get<1>(instructions[i]) == 'a')
			{
				r_a *= 3;
			}
			else
			{
				r_b *= 3;
			}
		}
		else if(instruction == "inc")
		{
			if(std::get<1>(instructions[i]) == 'a')
			{
				r_a++;
			}
			else
			{
				r_b++;
			}
		}
		else if(instruction == "jmp")
		{
			i += std::get<2>(instructions[i]) - 1;
		}
		else if(instruction == "jie")
		{
			if(std::get<1>(instructions[i]) == 'a')
			{
				if(r_a % 2 == 0)
				{
					i += std::get<2>(instructions[i]) - 1;
				}
			}
			else
			{
				if(r_b % 2 == 0)
				{
					i += std::get<2>(instructions[i]) - 1;
				}
			}
		}
		else if(instruction == "jio")
		{
			if(std::get<1>(instructions[i]) == 'a')
			{
				if(r_a == 1)
				{
					i += std::get<2>(instructions[i]) - 1;
				}
			}
			else
			{
				if(r_b == 1)
				{
					i += std::get<2>(instructions[i]) - 1;
				}
			}
		}
	}
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	uint64_t r_a = 0;
	uint64_t r_b = 0;
	
	std::vector<std::tuple<std::string, char, int>> instructions;
	
	parseInput(instructions);
	
	executeInstructions(instructions, r_a, r_b);
	resultA = r_b;
	
	r_a = 1;
	r_b = 0;
	executeInstructions(instructions, r_a, r_b);
	resultB = r_b;
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
