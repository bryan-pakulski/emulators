#ifndef __DISPLAY8_HPP__
#define __DISPLAY8_HPP__

#include <SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../globals.hpp"

class display {
	private:
		SDL_Window* gWindow;
		SDL_Renderer* gRenderer;

		unsigned char gfx[ c8_display::INTERNAL_WIDTH * c8_display::INTERNAL_HEIGHT ];

		void drawPixel( int x, int y, SDL_Renderer* renderer);

	public:
		display();
		~display();

		void doUpdate();
		void clear();
		unsigned char getPixel(int index);
		void setPixel(int index, unsigned char value);
};


#endif