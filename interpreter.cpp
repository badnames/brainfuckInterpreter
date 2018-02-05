#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <vector>

std::string loadProgram(char* fileName); 

int main(int argc, char *argv[]) {

	if(argc != 2) {
		std::cout << "invalid input" << std::endl;
		return -1;
	}	

	constexpr int MAX_CELLS = 20;

	std::array<int, MAX_CELLS> cells;
	for(int i = 0; i < MAX_CELLS; i++) {
		cells[i] = 0;
	}

	int         currCell = 0;
	std::string program  = loadProgram(argv[1]);

	std::vector<int> loopEntries;

	for(int i = 0; i < program.length(); i++) {
		char curr      = program[i];
		
		switch(curr) {
			case '+':
				cells[currCell]++;
			break;

			case '-':
				cells[currCell]--;
			break;

			case '<':
				if(currCell > 0)
					currCell--;
			break;

			case '>':
				if(currCell < MAX_CELLS)
					currCell++;
			break;

			case '.':
				if(cells[currCell] > 0 &&
				   cells[currCell] < 255)
					std::cout << (char)cells[currCell];
				else
					std::cout << cells[currCell];
					
			break;

			case ':':
			       std::cout << cells[currCell];
			break;

			case ',':
				std::cin >> cells[currCell];
			break;

			case '[':
				loopEntries.push_back(i);			
			break;

			case ']':
				if(cells[currCell] != 0) {
					//i doesn't need to be incremented here
					i = loopEntries[loopEntries.size() - 1];
				} else {
					loopEntries.pop_back();
				}
			break;

			case '!':
			break;

			default:
			break;
		}
	}
	
	//flush buffer and end with a new line
	std::cout << "" << std::endl;
}

std::string loadProgram(char* fileName) {
	std::string output;
	std::string line;
	std::ifstream file(fileName);
	
	if(!file.is_open())
		std::cout << "unable to open file" << std::endl;

	while(getline(file, line)) {
		output.append(line);
	}

	file.close();

	return output;	
}
