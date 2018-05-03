#include "decoder.hpp"

using namespace std;

decoder::decoder(string game_path) : path(game_path)
{
	cout << "Loading game from... " << path;

	for (auto &i: game_data)
	{
		i = NON_DATAFLAG;
	}

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
	ifstream game;
	game.open(path);
	game.width(4);

	int index = 0;
	while ( !game.eof() )
	{
		char* opcode = "";

		switch( game.peek() )
		{
			case ' ':
				game.ignore(1);
				break;

			default:
				game >> opcode;
				cout << opcode;
				//char test = hex(opcode);
				break;
		}

		//game_data[index] = opcode;

		index++;
	}

	game.close();
}