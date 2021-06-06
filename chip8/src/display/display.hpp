#ifndef __DISPLAY8_HPP__
#define __DISPLAY8_HPP__

#include <SDL.h>
#include <SDL2/SDL_ttf.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 320;

namespace c8_display {
	const int INTERNAL_WIDTH = 64;
	const int INTERNAL_HEIGHT = 32;
}

class display {
	private:
		SDL_Window* gWindow;
		SDL_Renderer* gRenderer;

		unsigned int gfx[ c8_display::INTERNAL_WIDTH * c8_display::INTERNAL_HEIGHT ];

	public:
		display();
		~display();
		
		// Update loop
		void doUpdate();
		void drawPixel( int x, int y, SDL_Renderer* renderer);
		void clear();
};


#endif