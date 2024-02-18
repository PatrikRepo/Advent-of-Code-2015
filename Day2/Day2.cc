#include <iostream>
#include <fstream>

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	std::string line;
	int width = 0;
	int height = 0;
	int length = 0;
	int area1 = 0;
	int area2 = 0;
	int area3 = 0;
	int volume = 0;

	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input,line))
		{
			size_t pos = 0;
			size_t secondPos = 0;
			pos = line.find_first_of("x");
			secondPos = line.find_first_of("x", pos+1);
			
			length = std::stoi(line.substr(0,pos));
			width = std::stoi(line.substr(pos+1,secondPos-pos-1));
			height = std::stoi(line.substr(secondPos+1));
			
			volume = length*width*height;
			area1 = length*width;
			area2 = length*height;
			area3 = width*height;
			
			resultA += (2*area1) + (2*area2) + (2*area3);
			if(area1 <= area2 && area1 <= area3)
			{
				resultA += area1;
			} 
			else if(area2 <= area1 && area2 <= area3)
			{
				resultA += area2;
			}
			else
			{
				resultA += area3;
			}
			
			resultB += volume;
			
			if(length >= height && length >= width)
			{
				resultB += (2*height) + (2*width);
			} 
			else if(height >= length && height >= width)
			{
				resultB += (2*length) + (2*width);
			}
			else
			{
				resultB += (2*length) + (2*height);
			}
		}
	}
	input.close();

	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
