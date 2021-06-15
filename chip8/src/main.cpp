#include <iostream>
#include "chip8.hpp"

using namespace std;

/**
 * Prints out the usage of the software
 *
 * @param argv arguments passed to executable
 *
 * @return	-1
 */
int usage(char* argv[])
{
	cout << "Usage: " << argv[0] << "'PATH TO GAME'";
	return -1;
}

/**
 * Main function for program
 *
 * @return     Returns int 0 on clean execution
 */
int main(int argc, char* argv[])
{
	// Usage note
	if (argc != 2)
		return usage(argv);

	// Initialise cpu and load rom
	chip8 c8 = chip8();
	if (c8.loadRomIntoMemory(argv[1])) {
		c8.gameloop();
	} else {
		cerr << "Error loading rom into memory, please check file path" << endl;
		return -1;
	}

	return 0;
}