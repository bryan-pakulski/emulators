#ifndef __CHIP8CPU_HPP__
#define __CHIP8CPU_HPP__

#include "memory.hpp"
#include "opcodes.hpp"
#include "decoder.hpp"

class opcode;

class cpu
{

	public:
		cpu(unsigned char (&g)[64*32]);
		~cpu();

		unsigned char* gfx;							// GFX memory buffer (stored in display class)
		memory mem = memory();
		bool drawFlag;
		bool clearScreen;

		void cycle();								// Contains function calls to complete 1 cycle

		// Getter and setter functions
		unsigned short getI();
		void setI( unsigned short value );

		unsigned short getPC();
		void incrementPC( int value );
		void setPC( unsigned short value );

		unsigned short getOP();
		void setOP( unsigned short value );

		unsigned char getV( int index );
		void setV( int index, unsigned char value );

		unsigned short popStatck();
		void pushStack( unsigned short value );

	private:
		unsigned char V[16] { 0 };					// CPU registers, 16th is carry flag
		unsigned short I;							// Index register
		unsigned short PC;							// Program counter 0x000 -> 0xFFF
		unsigned short op;							// Current opcode
		unsigned short stack[16] { 0 };				// Stack implementation
		unsigned short sp;							// Stack pointer

		opcode *lookup;

		unsigned short fetchNextOpcode();			// Fetch next opcode from memory
};

#endif