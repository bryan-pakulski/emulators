// handles loading games and parsing instructions
// to send into memory for the cpu

#ifndef __DECODER_HPP__
#define __DECODER_HPP__

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <bitset>

#define MAX_GAMESIZE 8192 // Max 8kb games

class decoder
{
	public:
		explicit decoder( char* game_path );
		~decoder();

		// Loads a game via internal path
		void loadGame();

		bool loaded;

	private:
		std::string path;
		std::vector<char> game_buffer;
};

#endif