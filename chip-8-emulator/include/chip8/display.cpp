#include "display.hpp"

using namespace std;

display::display()
{

}

display::~display()
{
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	SDL_Quit();
}

/**
 * @brief      Initialises SDL display
 *
 * @return     returns true if display correctly initialised
 */
bool display::initialiseDisplay()
{
	gWindow = NULL;
	gRenderer = NULL;

	// Initialise SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		cerr << "SDL could not be initialised with error: " << SDL_GetError() << endl;
		return false;
	}
	else
	{
		gWindow = SDL_CreateWindow(
			"chip8 emu",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);

		// Check display is initialised and finish creating SDL surface
		if (!gWindow)
		{
			cerr << "Window could not be created " << SDL_GetError() << endl;
			return false;
		}
		else
		{
			// Initialise renderer for window
			gRenderer= SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if ( !gRenderer )
			{
				cerr << "Renderer could not be created " << SDL_GetError() << endl;
				return false;
			}
			else
			{
				// Set up render properties
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
			}
		}
	}

	return true;
}

/**
 * @brief      Updates SDL display
 */
void display::doUpdate()
{
	// Clears the screen
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
	SDL_RenderClear( gRenderer );

	// TODO:
	// Add render code
	SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );		
	SDL_RenderFillRect( gRenderer, &fillRect );

	// Updates display
	SDL_RenderPresent( gRenderer );
}