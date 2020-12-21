#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <string.h>

// EMULATOR WIDTH MUST BE AN EVEN DIVISION OF THE ACTUAL SCREEN WIDTH
// This is a limitation in the drawPixel function as ratios are calculated as
// an int value
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 320;
const int EM_WIDTH = 64;
const int EM_HEIGHT = 32;

class display
{
	public:
		display();
		~display();

		// Iinitialise SDL window
		bool initialiseDisplay();
		
		// Update loop
		void doUpdate();
		void drawPixel( int x, int y, SDL_Renderer* renderer);

		void clear();

		bool init_flag;

		unsigned char gfx[ EM_WIDTH * EM_HEIGHT ];

	private:
		SDL_Window* gWindow;
		SDL_Renderer* gRenderer;
		
};


#endif