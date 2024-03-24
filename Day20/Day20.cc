#include <iostream>
#include <fstream>

uint64_t parseInput()
{
	uint64_t result = 0;
	std::string line;
   
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		getline(input, line);
		result = std::stoll(line);
	}
	return result;
}

uint64_t calculatePrimeSum(const uint64_t number)
{
	uint64_t result = 0;
	uint64_t n = 1;
	bool done = false;

	while(!done)
	{
		uint64_t sum = 0;
		for(uint64_t i=1; i<=n; i++)
		{
			if(n%i == 0)
			{
				sum += 10*i;
				if(sum >= number)
				{
					done = true;
					result = n;
					break;
				}
			}
		}
		n *= 10;
	}

	done = false;
	n /= 100;
	n *= 80;
	n /= 100;
	while(!done)
	{
		uint64_t sum = 0;
		uint64_t checkNumber = number - 10*n;
		for(uint64_t i=1; i<=n/2; i++)
		{
			if(n%i == 0)
			{
				sum += 10*i;
				if(sum >= checkNumber)
				{
					done = true;
					result = n;
					break;
				}
			}
		}
		n += 2;
	}
	return result;
}


uint64_t calculateNewPrimeSum(const uint64_t number)
{
	uint64_t result = 0;
	uint64_t n = 1;
	bool done = false;

	while(!done)
	{
		uint64_t sum = 0;
		for(uint64_t i=n; i>=1; i--)
		{
			if(n%i == 0)
			{
				if(n/i <= 50)
				{
					sum += 11*i;
					if(sum >= number)
					{
						done = true;
						result = n;
						break;
					}
				}
				else
				{
					break;
				}
			}
		}
		n *= 10;
	}

	done = false;
	n /= 100;
	n *= 85;
	n /= 100;
	while(!done)
	{
		uint64_t sum = 0;
		uint64_t checkNumber = number - n*11;
		for(uint64_t i=n/2; i>=1; i--)
		{
			if(n%i == 0)
			{
				if(n/i <= 50)
				{
					sum += 11*i;
					if(sum >= checkNumber)
					{
						done = true;
						result = n;
						break;
					}
				}
				else
				{
					break;
				}
			}
		}
		n += 2;
	}
	return result;
}

int main()
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;

	uint64_t number = parseInput();
 
	resultA = calculatePrimeSum(number);
	resultB = calculateNewPrimeSum(number);
 
	std::cout << "resultA: " << resultA << std::endl;
	std::cout << "resultB: " << resultB << std::endl;
  return 0;
}
