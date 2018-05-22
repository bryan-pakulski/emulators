#include "cpu.hpp"

cpu::cpu()
{
	PC = 0x200; // Program counter starts at 0x200
	op = 0;
	I = 0;

	// Initialise opcode hastable
	lookup = new opcode( this );
}

cpu::~cpu()
{

}

/**
 * Getter and setter functions for member variables
 */

unsigned short cpu::getI()
{
	return I;
}

void cpu::setI( unsigned short value )
{
	I = value;
}

unsigned short cpu::getPC()
{
	return PC;
}

void cpu::setPC( unsigned short value )
{
	PC = value;
}

unsigned short cpu::getOP()
{
	return op;
}

void cpu::setOP( unsigned short value )
{
	op = value;
}

unsigned char cpu::getV(int index)
{
	return V[index];
}

void cpu::setV(int index, unsigned char value)
{
	V[index] = value;
}

/**
 * @brief      Fetch next opcode
 *
 * @return     Returns combined opcodes to form a single instruction
 */
unsigned short cpu::fetchNextOpcode()
{
	return( mem.get(PC) << 8 | mem.get(PC + 1) );
}

/**
 * @brief      Call functions to complete 1 cpu cycle
 */
void cpu::cycle()
{
	// Fetch opcode
	op = fetchNextOpcode();
	
	// Decode opcode and execute
	lookup->execute( op );
}