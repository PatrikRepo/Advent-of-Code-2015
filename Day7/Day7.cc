#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>

struct Wire
{
	std::vector<std::string> outputWires;
	std::vector<uint16_t> inputSignals;
	uint16_t signal = 0;
	char operation = 0;
	int waitingFor = 0;
	int shift = 0;
	int numberOfInputWires = 0;
	int constant = 0;
	bool constantSet = false;
	void send(std::queue<std::string> &queue, std::unordered_map<std::string,Wire> &map)
	{
		for(auto it=outputWires.begin(); it!=outputWires.end(); it++)
		{
			(map[(*it)].inputSignals).push_back(signal);
			map[(*it)].waitingFor -= 1;
			queue.push((*it));
		}
	}
	void receive(std::queue<std::string> &queue, std::unordered_map<std::string,Wire> &map)
	{
		if(waitingFor==0)
		{
			switch(operation)
			{
				case '&':
					signal = (inputSignals.front() & inputSignals.back());
					break;
				case '|':
					signal = (inputSignals.front() | inputSignals.back());
					break;
				case '~':
					signal = (~inputSignals.front());
					break;
				case '<':
					signal = (inputSignals.front() << shift);
					break;
				case '>':
					signal = (inputSignals.front() >> shift);
					break;
				case 0:
					signal = (inputSignals.front());
			}
			waitingFor--;	
			send(queue, map);	
		}
	}
};

void parseInput(std::unordered_map<std::string,Wire> &map, std::queue<std::string> &queue)
{
	std::string line;
	
	std::ifstream input("input.txt");
	if(input.is_open())
	{
		while(getline(input,line))
		{
			std::string outputWireName;
			size_t pos = 0;
			pos = line.find_last_of(" ");
			outputWireName = line.substr(pos+1);
			if(map.count(outputWireName) == 0)
			{
				map[outputWireName] = Wire();
			}
			Wire* outputWire = &map[outputWireName];
			
			size_t finalpos = line.find_first_of("-");
			pos = 0;
			size_t endpos = line.find_first_of(" ");
			
			while(pos<finalpos)
			{
				std::string word = line.substr(pos,endpos-pos);
				if(std::isdigit(word[0]))
				{
					uint16_t number = std::stoi(word);
					if(outputWire->operation == '>' || outputWire->operation == '<')
					{
						outputWire->shift = number;
					}
					else
					{
						outputWire->inputSignals.push_back(number);
						outputWire->constant = number;
						outputWire->constantSet = true;
					}
				}
				else
				{
					switch(word[0])
					{
						case 'A':
							outputWire->operation = '&';
							break;
						case 'O':
							outputWire->operation = '|';
							break;
						case 'N':
							outputWire->operation = '~';
							break;
						case 'L':
							outputWire->operation = '<';
							break;
						case 'R':
							outputWire->operation = '>';
							break;
						default:
							if(map.count(word) == 0)
							{
								map[word] = Wire();
							}
							Wire* inputWire = &map[word];
							inputWire->outputWires.push_back(outputWireName);
							outputWire->numberOfInputWires += 1;
					}
				}
				pos = line.find_first_not_of(" ", endpos);
				endpos = line.find_first_of(" ", pos);
			}
			outputWire->waitingFor = outputWire->numberOfInputWires;
			if(outputWire->numberOfInputWires == 0)
			{
				queue.push(outputWireName);
			}
		}
	}
	input.close();
}

void sendMessages(std::unordered_map<std::string,Wire> &map, std::queue<std::string> &queue)
{
	while(!queue.empty())
	{
		map[queue.front()].receive(queue, map);
		queue.pop();
	}
}

int main()
{
	uint16_t resultA = 0;
	uint16_t resultB = 0;
	std::unordered_map<std::string,Wire> map;
	std::queue<std::string> queue;
	
	parseInput(map, queue);
	
	sendMessages(map, queue);
	
	resultA = map["a"].signal;
	
	for(auto it=map.begin(); it!=map.end(); it++)
	{
		it->second.waitingFor = it->second.numberOfInputWires;
		it->second.inputSignals.clear();
		if(it->second.constantSet)
		{
			it->second.inputSignals.push_back(it->second.constant);
		}
		if(it->second.numberOfInputWires == 0)
		{
			queue.push(it->first);
		}
	}
	map["b"].inputSignals.clear();
	map["b"].inputSignals.push_back(resultA);
	
	sendMessages(map, queue);
	resultB = map["a"].signal;
	
	std::cout << "resultA: " << resultA << '\n';
	std::cout << "resultB: " << resultB << std::endl;
	
	return 0;
}
