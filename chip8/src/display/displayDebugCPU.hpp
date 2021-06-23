#ifndef __DISPLAY8_DEBUG_HPP__
#define __DISPLAY8_DEBUG_HPP__

#include <SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>

#include "../cpu/cpu.hpp"
#include "../globals.hpp"

class displayDebugCPU {
	private:
		SDL_Window* gWindow;
		SDL_Renderer* gRenderer;
		TTF_Font* font;

	public:
		displayDebugCPU();
		~displayDebugCPU();

		void doUpdate(cpu* proc);
};

#endif