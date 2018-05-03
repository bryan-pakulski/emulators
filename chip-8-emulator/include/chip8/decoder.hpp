// handles loading games and parsing instructions
// to send into memory for the cpu

#ifndef __DECODER_HPP__
#define __DECODER_HPP__

#include <iostream>
#include <string>
#include <fstream>

#define MAX_GAMESIZE 1024
#define NON_DATAFLAG 0xFF // Flag for non game data in memory

class decoder
{
	public:
		decoder(std::string game_path);
		~decoder();

		// Loads a game via internal path
		void loadGame();

	private:
		std::string path;
		unsigned char game_data[MAX_GAMESIZE];
};

#endif