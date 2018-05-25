#include "decoder.hpp"

using namespace std;

decoder::decoder(char *game_path, memory *m) : mem(m), path(game_path)
{
	cout << "Loading game from... " << path << endl;

	loadGame();

	loadMem();
}

decoder::~decoder()
{
	delete mem;
}


/**
 * @brief      Loads a ROM file into the game buffer
 */
void decoder::loadGame()
{
	// Load into buffer
	ifstream game( path, std::ios::binary );

	game_buffer = vector<unsigned char>(
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
		cerr << "Game loaded successfully into buffer..." << endl;
		loaded = true;
	}

	game.close();
}

/**
 * @brief      Loads the game buffer into memory
 */
void decoder::loadMem()
{	
	cerr << "Loading game into memory..." << endl;

	int index = 0x200;
	for ( unsigned char &value : game_buffer )
	{
		mem->set(index, value);
	}

	cerr << "Successfully loaded game into memory..." << endl;
}