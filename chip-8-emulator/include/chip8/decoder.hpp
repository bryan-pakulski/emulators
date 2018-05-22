// handles loading games and parsing instructions
// to send into memory for the cpu

#ifndef __DECODER_HPP__
#define __DECODER_HPP__

#include "memory.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bitset>

#define MAX_GAMESIZE 0x0DFF // Based on memory range of 0x200 - 0xFFF

// Forward declaration
class memory;

class decoder
{
	public:
		explicit decoder( char* game_path, memory *m );
		~decoder();

		void loadGame();
		void loadMem();

		bool loaded;

	private:

		// Decoder needs access to memory in order to get/set appropriate values
		memory *mem;

		std::string path;
		std::vector<char> game_buffer;
};

#endif