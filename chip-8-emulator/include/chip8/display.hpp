#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#include <SDL.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class display
{
	public:
		display();
		~display();

		// Iinitialise SDL window
		bool initialiseDisplay();
		// Update loop
		void doUpdate();

		bool init_flag;

	private:
		SDL_Window* window;
		SDL_Surface* screenSurface;
};


#endif