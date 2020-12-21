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
 * @brief      Draws a "pixel" on screen, each pixel is multiplied by screen ratio so in reality it's 10px or so big
 *
 * @param[in]  x         x position relative to the emulator screen width, max 63
 * @param[in]  y         y position relvative to the emulator screen height, max 31
 * @param      renderer  The renderer to draw to
 */
void display::drawPixel( int x, int y, SDL_Renderer* renderer)
{
	// Sanity check
	if ( ( x > EM_WIDTH - 1 || y > EM_HEIGHT - 1 ) || ( x < 0 || y < 0 ) )
		cerr << "Rendering error, drawing offscreen at coordinates " << x << ", " << y << endl;

	int ratioW = SCREEN_WIDTH / EM_WIDTH;
	int ratioH = SCREEN_HEIGHT / EM_HEIGHT;

	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_Rect rect = { x * ratioW, y * ratioH, SCREEN_WIDTH / EM_WIDTH, SCREEN_HEIGHT / EM_HEIGHT };
	SDL_RenderFillRect(renderer, &rect);
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
 * @brief      Clears gfx memory buffer
 *
 */
void display::clear()
{
	memset(gfx, 0, sizeof(gfx));
}


/**
 * @brief      Updates SDL display
 */
void display::doUpdate()
{	
	// Clears the screen
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
	SDL_RenderClear( gRenderer );

	// Draw GFX array to screen
	for (int i = 0; i < EM_WIDTH; i++)
	{
		for (int j = 0; j < EM_HEIGHT; j++)
		{
			if (gfx[ EM_WIDTH * j + i] == 1)
				drawPixel(i, j, gRenderer);
		}
	}

	// Updates display
	SDL_RenderPresent( gRenderer );
}