#include "displayDebugCPU.hpp"

displayDebugCPU::displayDebugCPU() {
	// Initialise SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		throw std::runtime_error(SDL_GetError());
	} else {
		gWindow = SDL_CreateWindow(
			"chip8 emu - DEBUG",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			c8_display::SCREEN_WIDTH_DEBUG,
			c8_display::SCREEN_HEIGHT_DEBUG,
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

		if ( TTF_Init() < 0 ) {
			throw std::runtime_error(TTF_GetError());
		}
	}

	// Initialise fonts
	font = TTF_OpenFont("OpenSans-Regular.ttf", 16);
	if (!font) {
		throw std::runtime_error(TTF_GetError());
	}
}

displayDebugCPU::~displayDebugCPU() {
	TTF_CloseFont(font);
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	TTF_Quit();
	SDL_Quit();
	
}

/**
 * Updates SDL display
 */
void displayDebugCPU::doUpdate(cpu* proc)
{	
	// Clears the screen
	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 );
	SDL_RenderClear( gRenderer );

	// TODO: draw debug information

	// Updates display
	SDL_RenderPresent( gRenderer );
}