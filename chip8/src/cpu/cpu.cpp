#include "cpu.hpp"
#include <vector>
#include <fstream>

cpu::cpu(memory* m) {
	mem = m;
	op_lookup = new opcodes();
	drawFlag = true;
	clearScreen = true;
	I = 0;
	PC = 0x200;
	op = 0;
	sp = 0;
}

cpu::~cpu() {
	delete op_lookup;
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

unsigned short cpu::getV(int index)
{
	return V[index];
}

void cpu::setV(int index, unsigned short value)
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
 * @brief Pushes to stack and increments stack pointer to stop data overwriting
 *
 * @param value  The value to push
 */
void cpu::pushStack( unsigned short value )
{
	stack[sp] = value;
	++sp;
}

/**
 * Fetch next opcode
 *
 * @return Returns combined opcodes to form a single instruction
 */
unsigned short cpu::fetchNextOpcode()
{
	//BUG: opcode gets handled incorrectly
	//BUG: value is returned normally from fetchNextOpcode, but when passed to function pointer value will change
	std::cerr << "Getting memory location/s: " << std::dec << PC << " | " << std::dec << PC+1 << std::endl;

	unsigned short opL = mem->get(PC);
	opL = opL << 8;
	unsigned short opR = mem->get(PC + 1);
	opR = opR & 0x00FF;

	unsigned short op = opL | opR;
	return(op);
}

/**
 * @brief      Call functions to complete 1 cpu cycle
 */
void cpu::cycle()
{
	// Fetch opcode
	op = fetchNextOpcode();

	// Decode opcode and execute
	func_p opCallFunction = op_lookup->get(op);
	opCallFunction(op, this);

	//TODO: Update timers
}