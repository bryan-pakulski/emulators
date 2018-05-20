#ifndef __CHIP8_HPP__
#define __CHIP8_HPP__

#include "decoder.hpp"
#include "cpu.hpp"
#include "memory.hpp"
#include "display.hpp"
#include <SDL.h>
#include <iostream>

class chip8
{
	public:
		explicit chip8( char* path );
		~chip8();

		// Performs all logic/display updates
		void gameloop();

	private:
		decoder *loader;
		display *screen;
		cpu *cp;
		bool running;
		
		SDL_Event e;
};


#endif