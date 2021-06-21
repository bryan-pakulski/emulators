#ifndef __CHIP8_INPUTHANDLER_HPP__
#define __CHIP8_INPUTHANDLER_HPP__

#include <SDL.h>
#include "../cpu/cpu.hpp"

class inputHandler {

	private:
		

	public:
		inputHandler();
		void processInput(SDL_Event e, cpu* proc);
};

#endif