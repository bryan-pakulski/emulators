#include "chip8.hpp"

using namespace std;

/**
 * @brief      Initialise all sections of the emulator
 *
 * @param      path  The path to the rom we are loading
 */
chip8::chip8( char* path )
{
	// Init SDL display
	screen = new display();

	// Initialise cpu and memory space so that the loader can access it
	// Pass through memory buffer to CPU for access
	cp     = new cpu( screen->gfx );

	loader = new decoder( path, &cp->mem );
	
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

		// DEBUG dumps //

		// If gfx dump flag is set dump gfx memory
		if (cp->dumpGFX)
		{
			screen->dump_memory();
			cp->dumpGFX = !cp->dumpGFX;
		}

		// If mem dump flag is set dump cpu memory
		if (cp->dumpMem)
		{
			cp->mem.dump_memory();
			cp->dumpMem = !cp->dumpMem;
		}
		
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
			cp->clearScreen = !cp->clearScreen;
			screen->clear();
		}
		// Update display when cpu draw flag is raised
		if ( cp->drawFlag )
		{
			screen->doUpdate();
			cp->drawFlag = !cp->drawFlag;
		}
	}
}