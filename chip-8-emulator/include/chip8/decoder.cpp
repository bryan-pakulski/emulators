#include "decoder.hpp"

using namespace std;

decoder::decoder(string game_path) : path(game_path)
{
	cout << "Loading game from... " << game_path;
}

decoder::~decoder()
{

}