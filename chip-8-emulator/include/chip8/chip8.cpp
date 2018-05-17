#include "chip8.hpp"

using namespace std;

/**
 * @brief      Initialise all sections of the emulator
 *
 * @param      path  The path to the rom we are loading
 */
chip8::chip8( char* path )
{
	loader = new decoder( path );
	screen = new display();

	running = screen->initialiseDisplay();

	if (running)
		gameloop();
	else
		cerr << "Emulator could not be initialised" << endl;
}

chip8::~chip8()
{

}

void chip8::gameloop()
{
	while (running)
	{
		// Get events from queue
		while ( SDL_PollEvent( &e ) != 0 )
		{
			if (e.type == SDL_QUIT)
				running = false;
		}

		// update non event opcodes

		// TODO:
		// Update display when cpu draw flag is raised
		screen->doUpdate();
	}
}