#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <utility>

struct Ingredient
{
	int capacity = 0;
	int durability = 0;
	int flavor = 0;
	int texture = 0;
	int calories = 0;
	Ingredient(int c, int d, int f, int t, int clr) : capacity(c), durability(d), flavor(f), texture(t), calories(clr) {}
};

void parseInput(std::vector<Ingredient> &ingredients)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input,line))
		{
			size_t pos = 0;
			size_t endpos = 0;
			
			pos = line.find_first_of("1234567890", endpos);
			if(line[pos-1] == '-')
			{
				pos--;
			}
			endpos = line.find_first_of(" ", pos);
			int capacity = std::stoi(line.substr(pos,endpos-pos));
			
			pos = line.find_first_of("1234567890", endpos);
			if(line[pos-1] == '-')
			{
				pos--;
			}
			endpos = line.find_first_of(" ", pos);
			int durability = std::stoi(line.substr(pos,endpos-pos));
			
			pos = line.find_first_of("1234567890", endpos);
			if(line[pos-1] == '-')
			{
				pos--;
			}
			endpos = line.find_first_of(" ", pos);
			int flavor = std::stoi(line.substr(pos,endpos-pos));
			
			pos = line.find_first_of("1234567890", endpos);
			if(line[pos-1] == '-')
			{
				pos--;
			}
			endpos = line.find_first_of(" ", pos);
			int texture = std::stoi(line.substr(pos,endpos-pos));
			
			pos = line.find_first_of("1234567890", endpos);
			if(line[pos-1] == '-')
			{
				pos--;
			}
			endpos = line.find_first_of(" ", pos);
			int calories = std::stoi(line.substr(pos,endpos-pos));
			
			ingredients.push_back(Ingredient(capacity, durability, flavor, texture, calories));
		}
	}
	input.close();
}

uint64_t recursive10(const std::vector<Ingredient> &ingredients, int capacity, int durability, int flavor, int texture, int calories, const int count, const bool calorieLimit)
{
	uint64_t result = 0;
	
	if(count < 10)
	{
		uint64_t newResult = 0;
		
		newResult = recursive10(ingredients, capacity + ingredients[0].capacity, durability + ingredients[0].durability, flavor + ingredients[0].flavor, texture + ingredients[0].texture, calories + ingredients[0].calories, count+1, calorieLimit);
		if(result < newResult)
		{
			result = newResult;
		}
		
		newResult = recursive10(ingredients, capacity + ingredients[1].capacity, durability + ingredients[1].durability, flavor + ingredients[1].flavor, texture + ingredients[1].texture, calories + ingredients[1].calories, count+1, calorieLimit);
		if(result < newResult)
		{
			result = newResult;
		}
		
		newResult = recursive10(ingredients, capacity + ingredients[2].capacity, durability + ingredients[2].durability, flavor + ingredients[2].flavor, texture + ingredients[2].texture, calories + ingredients[2].calories, count+1, calorieLimit);
		if(result < newResult)
		{
			result = newResult;
		}
		
		newResult = recursive10(ingredients, capacity + ingredients[3].capacity, durability + ingredients[3].durability, flavor + ingredients[3].flavor, texture + ingredients[3].texture, calories + ingredients[3].calories, count+1, calorieLimit);
		if(result < newResult)
		{
			result = newResult;
		}
	}
	else
	{
		if(capacity < 0)
		{
			capacity = 0;
		}
		if(durability < 0)
		{
			durability = 0;
		}
		if(flavor < 0)
		{
			flavor = 0;
		}
		if(texture < 0)
		{
			texture = 0;
		}
		if(!calorieLimit || calories == 500)
		{
			result = flavor*texture;
			result *= durability;
			result *= capacity;
		}
	}
	
	return result;
}

std::pair<uint64_t,uint64_t> calculatePoints(const std::vector<Ingredient> &ingredients)
{
	uint64_t resultA = 0;
	uint64_t resultB = 0;
	
	//Given the input it takes 12 tbs to make something that has positive values in all categories which are: 3, 3, 2, 1. Which contains 86 calories.
	//We want to maximize the hypervolume of the hypercube, and by adding 1 sugar, 2 candy and 3 chocolate we end up with 4, 3, 4, 4 which is the highest hypervolume in 18 tbs. 18*5 = 90 tbs with 20 15 20 20. This contains 430 calories.
	//Then do a recursive search through the rest of the 10 ingredients.
	//TODO: Make general
	resultA = recursive10(ingredients, 20, 15, 20, 20, 430, 0, false);
	resultB = recursive10(ingredients, 20, 15, 20, 20, 430, 0, true);
	
	return std::make_pair(resultA,resultB);
}

int main()
{
	std::pair<uint64_t,uint64_t> result;
	std::vector<Ingredient> ingredients;
	
	parseInput(ingredients);
	
	result = calculatePoints(ingredients);
	
	std::cout << "resultA: " << result.first << std::endl;
	std::cout << "resultB: " << result.second << std::endl;
	return 0;
}
