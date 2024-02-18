#include <iostream>
#include <fstream>

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::string line;
	uint64_t codeCount = 0;
	uint64_t stringCount = 0;
	uint64_t newCodeCount = 0;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input,line))
		{
			uint64_t localCodeCount = line.length();
			uint64_t localStringCount = localCodeCount -2;
			uint64_t localNewCodeCount = localCodeCount +2;
			for(unsigned int i=0; i<line.length(); i++)
			{
				if(line[i] == '\\' || line[i] == '"')
				{
					localNewCodeCount++;
					if(line[i] == '\\')
					{
						switch(line[i+1])
						{
							case '\\':
								localStringCount--;
								localNewCodeCount++;
								i++;
								break;
							case '"':
								localStringCount--;
								break;
							case 'x':
								localStringCount -= 3;
								i += 3;
						}
					}		
				}
			}
			codeCount += localCodeCount;
			stringCount += localStringCount;
			newCodeCount += localNewCodeCount;
		}
	}
	input.close();
	
	resultA = codeCount - stringCount;
	resultB = newCodeCount - codeCount;
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
