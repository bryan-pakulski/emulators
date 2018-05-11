#ifndef __CPU_HPP__
#define __CPU_HPP__

#include "memory.hpp"

class cpu
{

	public:
		cpu();
		~cpu();

	private:
		unsigned short opcode;	// Current opcode
		unsigned char V[16];		// CPU registers, 16th is carry flag
		unsigned short I;				// Index register
		unsigned short PC;			// Program counter 0x000 -> 0xFFF

		memory mem = memory();

};

#endif