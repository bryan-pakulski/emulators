#include "decoder.hpp"

using namespace std;

decoder::decoder(char* game_path) : path(game_path)
{
	cout << "Loading game from... " << path << endl;

	loadGame();
}

decoder::~decoder()
{

}

/**
 * Loads a ROM file into game_data
 */
void decoder::loadGame()
{
	// Load into buffer
	ifstream game( path, std::ios::binary );

	game_buffer = vector<char>(
		(istreambuf_iterator<char>(game)),
		(istreambuf_iterator<char>())
	);

	if (game_buffer.size() > MAX_GAMESIZE)
	{
		cerr << "Error; maximum game size exceeded" <<
		"Current limit is: " << MAX_GAMESIZE << " bytes" << endl;
		loaded = false;
	}
	else
	{
		cerr << "Game loaded successfully into memory..." << endl;
		loaded = true;
	}

	game.close();
}