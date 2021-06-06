#ifndef __CHIP8_HPP__
#define __CHIP8_HPP__

#include <iostream>

#include "memory/memory.hpp"
#include "cpu/cpu.hpp"
#include "display/display.hpp"

class chip8 {
	private:
		memory *mem;
		cpu *proc;
		display *gfx;

	public:
		chip8();
		~chip8();
		
		void gameloop(float dt);
		bool loadRomIntoMemory(char* filepath);
		
};


#endif