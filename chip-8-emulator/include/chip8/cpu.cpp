#include "cpu.hpp"

cpu::cpu(unsigned int (&g)[64*32]) : drawFlag( true ), clearScreen( true ),
						 I( 0 ), PC( 0x200 ), op( 0 ), sp( 0 )
{
	// Initialise opcode hastable
	lookup = new opcode( this );

	// Dump memory on init for debugging
	dumpMem = true;

	// Map memory buffer to local variable	
	gfx = g;
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

void cpu::incrementPC( int value )
{
	PC += ( 2 * value );
}

void cpu::setPC( unsigned short value)
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

unsigned short cpu::popStack()
{
	--sp;
	unsigned short val = stack[sp];

	return val;
}

/**
 * @brief      Pushes to stack and increments stack pointer to stop data overwriting
 *
 * @param[in]  value  The value to index
 */
void cpu::pushStack( unsigned short value )
{
	stack[sp] = value;
	++sp;
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

	// Update timers
}