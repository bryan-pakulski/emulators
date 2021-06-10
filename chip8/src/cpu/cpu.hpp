#ifndef __CPU8_HPP__
#define __CPU8_HPP__

#include <SDL.h>
#include <iostream>

#include "../display/display.hpp"
#include "../memory/memory.hpp"
#include "opcodes.hpp"

class opcodes;
class display;

class cpu {
	private:
		opcodes* op_lookup;

		unsigned short V[16] { 0 };					// CPU registers, 16th is carry flag
		unsigned short I;							// Index register
		unsigned short PC;							// Program counter 0x000 -> 0xFFF
		unsigned short op;							// Current opcode
		unsigned short stack[16] { 0 };				// Stack implementation
		unsigned short sp;							// Stack pointer

		unsigned short fetchNextOpcode();			// Fetch next opcode from memory

	public:
		cpu(memory* m, display* g);
		~cpu();

		// Public flags
		bool drawFlag;
		bool clearScreen;
		unsigned short delay_timer = 0x0;
		unsigned short sound_timer = 0x0;

		memory* mem;
		display* gfx;

		// Getter and setter functions
		unsigned short getI();
		void setI( unsigned short value );

		unsigned short getPC();
		void incrementPC( int value );
		void setPC( unsigned short value );

		unsigned short getOP();
		void setOP( unsigned short value );

		unsigned short getV( int index );
		void setV( int index, unsigned short value );

		unsigned short popStack();
		void pushStack( unsigned short value );

		void cycle();
		
};


#endif