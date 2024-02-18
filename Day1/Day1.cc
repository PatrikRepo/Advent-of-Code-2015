#include <iostream>
#include <fstream>

int main()
{
	int64_t resultA = 0;
	int64_t resultB = 0;
	std::string line;
	bool resultBSet = false;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, line);
		for(unsigned int i=0; i<line.length(); i++)
		{
			if(line[i] == '(')
			{
				resultA++;
			}
			else
			{
				resultA--;
			}
			if(!resultBSet && resultA < 0)
			{
				resultB = i+1;
				resultBSet = true;
			}
		}
	}
	input.close();

	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
