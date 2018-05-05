// handles loading games and parsing instructions
// to send into memory for the cpu

#ifndef __DECODER_HPP__
#define __DECODER_HPP__

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bitset>

#define MAX_GAMESIZE 1024

class decoder
{
	public:
		explicit decoder( std::string game_path );
		~decoder();

		// Loads a game via internal path
		void loadGame();

	private:
		std::string path;
		std::vector<char> game_buffer;
};

#endif