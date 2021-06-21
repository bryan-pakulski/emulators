#ifndef __CHIP8_HPP__
#define __CHIP8_HPP__

#include <iostream>

#include "cpu/taskScheduler.hpp"
#include "cpu/cpu.hpp"
#include "display/display.hpp"
#include "input/inputHandler.hpp"
#include "memoryc8/memoryc8.hpp"

typedef void(*cpuCycle)(cpu*);

class chip8 {
	private:
		memoryc8 *mem;
		cpu *proc;
		display *gfx;
		taskScheduler<cpuCycle, cpu*> *cpuScheduler;
		inputHandler *in;
		
		SDL_Event e;

	public:
		chip8();
		~chip8();
		
		void gameloop();
		bool loadRomIntoMemory(char* filepath);
		
};


#endif