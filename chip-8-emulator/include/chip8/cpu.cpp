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

	// Decode opcode (returns an index for the opcode lookup table)

}