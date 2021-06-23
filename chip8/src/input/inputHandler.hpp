#ifndef __CHIP8_INPUTHANDLER_HPP__
#define __CHIP8_INPUTHANDLER_HPP__

#include <map>
#include <SDL.h>
#include <SDL2/SDL_keycode.h>
#include "../cpu/cpu.hpp"

class inputHandler {

	private:
		// 0x0 -> 0xF
		std::map<char, int> keyMap = {
			{SDLK_1, 0}, {SDLK_2, 1}, {SDLK_3, 2}, {SDLK_4, 3},
			{SDLK_q, 4}, {SDLK_w, 5}, {SDLK_e, 6}, {SDLK_r, 7},
			{SDLK_a, 8}, {SDLK_s, 9}, {SDLK_d, 10}, {SDLK_f, 11},
			{SDLK_z, 12}, {SDLK_x, 13}, {SDLK_c, 14}, {SDLK_v, 15}, 
		};

	public:
		inputHandler();
		void processInput(SDL_Event e, cpu* proc);
};

#endif