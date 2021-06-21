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
			c8_display::SCREEN_WIDTH,
			c8_display::SCREEN_HEIGHT,
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
 * Returns value of internal gfx array at index
 *
 * @param index
 * @return gfx value at index
 */
unsigned char display::getPixel(int index) {
	if (index > c8_display::INTERNAL_WIDTH * c8_display::INTERNAL_HEIGHT) {
		throw std::runtime_error("Requested pixel outside of maximum range");
	}

	return gfx[index];
}

/**
 * Draws a "pixel" on screen, each pixel is multiplied by screen ratio so in reality it's 10px or so big
 *
 * @param x x position relative to the emulator screen width, max 63
 * @param y y position relvative to the emulator screen height, max 31
 */
void display::setPixel(int index, unsigned char value) {
	if (index > c8_display::INTERNAL_WIDTH * c8_display::INTERNAL_HEIGHT) {
		throw std::runtime_error("Requested pixel outside of maximum range");
	}

	gfx[index] = value;
}

/**
 * Draws a "pixel" on screen, each pixel is multiplied by screen ratio so in reality it's 10px or so big
 *
 * @param x x position relative to the emulator screen width, max 63
 * @param y y position relvative to the emulator screen height, max 31
 * @param renderer The renderer to draw to
 */
void display::drawPixel( int x, int y, SDL_Renderer* renderer)
{
	// Sanity check
	if ( ( x > c8_display::INTERNAL_WIDTH - 1 || y > c8_display::INTERNAL_HEIGHT - 1 ) || ( x < 0 || y < 0 ) )
		cerr << "Rendering error, drawing offscreen at coordinates " << x << ", " << y << endl;

	int ratioW = c8_display::SCREEN_WIDTH / c8_display::INTERNAL_WIDTH;
	int ratioH = c8_display::SCREEN_HEIGHT / c8_display::INTERNAL_HEIGHT;

	SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_Rect rect = { x * ratioW, y * ratioH, c8_display::SCREEN_WIDTH / c8_display::INTERNAL_WIDTH, c8_display::SCREEN_HEIGHT / c8_display::INTERNAL_HEIGHT };
	SDL_RenderFillRect(renderer, &rect);
}

/**
 * Updates SDL display
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
			if (gfx[ c8_display::INTERNAL_WIDTH * j + i] == 0xF)
				drawPixel(i, j, gRenderer);
		}
	}

	// Updates display
	SDL_RenderPresent( gRenderer );
}

void display::clear() {
	memset(gfx, 0x0, sizeof(gfx));
}