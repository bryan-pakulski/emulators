#include <iostream>
#include "chip8.hpp"
#include "decoder.hpp"

using namespace std;

/**
 * @brief      Prints out the usage of the software
 *
 * @param      arguments passed to executable
 *
 * @return     -1
 */
int usage(char* argv[])
{
	cout << "Usage: " << argv[0] << "'PATH TO GAME'";
	return -1;
}

/**
 * @brief      Main function for program
 *
 * @return     Returns int 0 on clean execution
 */
int main(int argc, char* argv[])
{
	// Usage note
	if (argc != 2)
		return usage(argv);
	
	decoder loader = decoder(argv[1]);

	return 0;
}