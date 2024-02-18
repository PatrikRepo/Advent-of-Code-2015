#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>

void parseInput(std::vector<std::pair<std::string,std::string>> &conversions, std::string &line)
{
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, line);
		while(line != "")
		{
			size_t pos = line.find_first_of(" ");
			std::string from = line.substr(0, pos);

			pos = line.find_first_of(">", pos) +2;
			std::string to = line.substr(pos);

			conversions.push_back(std::make_pair(from, to));

			getline(input, line);
		}
	getline(input, line);
	}
	input.close();
}

uint64_t calibrate(const std::vector<std::pair<std::string, std::string>> &conversions, const std::string line)
{
	uint64_t result = 0;
	std::unordered_map<std::string, int> createdMolecules;
	
	for(auto it=conversions.begin(); it!=conversions.end(); it++)
	{
		size_t pos = line.find_first_of((it->first)[0]);
		
		while(pos != std::string::npos)
		{
			if(it->first == line.substr(pos, it->first.length()))
			{
				std::string temp = line;
				temp.replace(pos, it->first.length(), it->second);
				createdMolecules[temp] += 1;
			}
			pos = line.find_first_of((it->first)[0], pos+1);
		}
	}
	
	result = createdMolecules.size();
	
	return result;
}

uint64_t steps(std::string &line)
{
  uint64_t result = 0;
 
  size_t pos = line.find_first_of("r");
 
  while(pos != std::string::npos)
  {
    if(line[pos-1] == 'A')
    {
      line.replace(pos-1, 1, "Z");
    }
    pos = line.find_first_of("r", pos+1);
  }
 
  pos = line.find_first_of("aghilnr");
 
  while(pos != std::string::npos)
  {
    line.erase(pos, 1);
    pos = line.find_first_of("aghilnr", pos);
  }
 
  int length = line.length();
  int Ys = 0;
  int YYs = 0;
  int Zs = 0;
  for(int i=0; i<length; i++)
  {
    if(line[i] == 'Y')
    {
      if(line[i+2] == 'Y')
      {
        YYs++;
        Zs--;
        i += 2;
      }
      else
      {
        Ys++;
        Zs--;
      }

    }
    if(line[i] == 'Z')
    {
      Zs++;
    }
  }
 
  result = length - 1 - (Zs*2) - (4*Ys) - (6*YYs);
 
  return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::vector<std::pair<std::string, std::string>> conversions;
	std::string line;
	
	parseInput(conversions, line);

	resultA = calibrate(conversions, line);
	resultB = steps(line);

	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
