#include "display.hpp"

#include <iostream>
#include <stdexcept>
#include <string.h>
#include <stdio.h>

using namespace std;

display::display() {
	clear();

	gWindow = NULL;
	gRenderer = NULL;

	// Initialise SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		throw std::runtime_error(SDL_GetError());
	} else {
		gWindow = SDL_CreateWindow(
			"chip8 emu",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);

		// Check display is initialised and finish creating SDL surface
		if (!gWindow) {
			throw std::runtime_error(SDL_GetError());
		} else {
			// Initialise renderer for window
			gRenderer= SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if ( !gRenderer ) {
				throw std::runtime_error(SDL_GetError());
			} else {
				// Set up render properties
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
			}
		}
	}

}

display::~display() {
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	SDL_Quit();
}

/**
 * @brief      Draws a "pixel" on screen, each pixel is multiplied by screen ratio so in reality it's 10px or so big
 *
 * @param[in]  x         x position relative to the emulator screen width, max 63
 * @param[in]  y         y position relvative to the emulator screen height, max 31
 * @param[in]      renderer  The renderer to draw to
 */
void display::drawPixel( int x, int y, SDL_Renderer* renderer)
{
	// Sanity check
	if ( ( x > c8_display::INTERNAL_WIDTH - 1 || y > c8_display::INTERNAL_HEIGHT - 1 ) || ( x < 0 || y < 0 ) )
		cerr << "Rendering error, drawing offscreen at coordinates " << x << ", " << y << endl;

	int ratioW = SCREEN_WIDTH / c8_display::INTERNAL_WIDTH;
	int ratioH = SCREEN_HEIGHT / c8_display::INTERNAL_HEIGHT;

	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_Rect rect = { x * ratioW, y * ratioH, SCREEN_WIDTH / c8_display::INTERNAL_WIDTH, SCREEN_HEIGHT / c8_display::INTERNAL_HEIGHT };
	SDL_RenderFillRect(renderer, &rect);
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
	for (int i = 0; i < c8_display::INTERNAL_WIDTH; i++)
	{
		for (int j = 0; j < c8_display::INTERNAL_HEIGHT; j++)
		{
			if (gfx[ c8_display::INTERNAL_WIDTH * j + i] == 0xFFFFFFFF)
				drawPixel(i, j, gRenderer);
		}
	}

	// Updates display
	SDL_RenderPresent( gRenderer );
}

void display::clear() {
	memset(gfx, 0x0, sizeof(gfx));
}