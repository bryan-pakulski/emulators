#ifndef __DISPLAY8_HPP__
#define __DISPLAY8_HPP__

#include <SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../globals.hpp"

class display {
	private:
		SDL_Window* gWindow;
		SDL_Renderer* gRenderer;

		unsigned int gfx[ c8_display::INTERNAL_WIDTH * c8_display::INTERNAL_HEIGHT ];

		void drawPixel( int x, int y, SDL_Renderer* renderer);

	public:
		display();
		~display();

		void doUpdate();
		void clear();
		unsigned int getPixel(int index);
		void setPixel(int index, int value);
};


#endif