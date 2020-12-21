#include "chip8.hpp"

using namespace std;

/**
 * @brief      Initialise all sections of the emulator
 *
 * @param      path  The path to the rom we are loading
 */
chip8::chip8( char* path )
{
	// Initialise cpu and memory space so that the loader can
	// Access it
	cp     = new cpu();

	loader = new decoder( path, &cp->mem );
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
		// Get events from queue and get keypad input
		while ( SDL_PollEvent( &e ) != 0 )
		{
			if (e.type == SDL_QUIT)
				running = false;
		}

		// Fetch and execute opcode
		cp->cycle();

		// Check if we need to clear the screen
		if ( cp->clearScreen )
		{
			// TODO: clear screen in SDL, below code reverses clear screen flag;
			cp->clearScreen = !cp->clearScreen;
		}
		// Update display when cpu draw flag is raised
		if ( cp->drawFlag )
		{
			screen->doUpdate();
			cp->drawFlag = !cp->drawFlag;
		}
	}
}