#include "display.hpp"

using namespace std;

display::display()
{

}

display::~display()
{
	SDL_Quit();
}

/**
 * @brief      Initialises SDL display
 *
 * @return     returns true if display correctly initialised
 */
bool display::initialiseDisplay()
{
	window = NULL;
	screenSurface = NULL;

	// Initialise SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		cout << "SDL could not be initialised with error: " << SDL_GetError() << endl;
		return false;
	}
	else
	{
		window = SDL_CreateWindow(
			"chip8 emu",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);

		// Check display is initialised and finish creating SDL surface
		if (!window)
		{
			cout << "Window could not be created " << SDL_GetError() << endl;
			return false;
		}
		else
			screenSurface = SDL_GetWindowSurface( window );
	}

	return true;
}

/**
 * @brief      Updates SDL display
 */
void display::doUpdate()
{

	SDL_UpdateWindowSurface( window );
}