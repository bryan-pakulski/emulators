#ifndef __CHIP8CPU_HPP__
#define __CHIP8CPU_HPP__

#include "memory.hpp"
#include "opcodes.hpp"

class opcode;

class cpu
{

	public:
		cpu();
		~cpu();

		void cycle();						// Contains function calls to complete 1 cycle

	private:
		unsigned char V[16];		// CPU registers, 16th is carry flag
		unsigned short I;				// Index register
		unsigned short PC;			// Program counter 0x000 -> 0xFFF
		unsigned short op;			// Current opcode

		memory mem = memory();
		opcode *lookup;

		unsigned short fetchNextOpcode();		// Fetch next opcode from memory
};

#endif