#include <iostream>
#include <fstream>

//This is taking the input into account. Honestly, I just solved both questions by just looking at the input and doing calculations in my head.
//In our input we have nothing matching our rules, except for the fact that we are far away from the forbidden characters
//The smallest key would then end on the for xxyzz where xyz and chars that are one apart from each other. Any other string would require at least six chars
//Had we already had a pair somewhere in the first four chars the smallest would be xxyz. Had we had two pairs the smallest would be xyz.
//Had we had a straight it would be xxxx
//It is easy to implement a checker, but why check for something I know not to be the case?
std::string nextPassword(std::string &line)
{
	std::string result;
	std::string temp = line;
	
	if(temp[3] <= 'x')
	{
		temp[4] = temp[3];
		temp[5] = temp[3]+1;
		temp[6] = temp[3]+2;
		temp[7] = temp[3]+2;
		if(temp.compare(line) > 0)
		{
			result = temp;
		}
		else
		{
			if(temp[3]+1 <= 'x')
			{
				for(int i=3; i<8; i++)
				{
					temp[i]++;
				}
				result = temp;
			}
			else
			{
				temp[2]++;
				temp[3] = 'a';
				temp[4] = 'a';
				temp[5] = 'b';
				temp[6] = 'c';
				temp[7] = 'c';
				result = temp;
			}
		}
	}
	else
	{
		temp[2]++;
		temp[3] = 'a';
		temp[4] = 'a';
		temp[5] = 'b';
		temp[6] = 'c';
		temp[7] = 'c';
	}
	
	return result;
}

int main()
{
	std::string resultA;
	std::string resultB;
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input,line);
	}
	input.close();
	
	resultA = nextPassword(line);
	resultB = nextPassword(resultA);
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
