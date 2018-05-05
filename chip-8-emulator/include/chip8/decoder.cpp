#include "decoder.hpp"

using namespace std;

decoder::decoder(string game_path) : path(game_path)
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

	game.close();
}