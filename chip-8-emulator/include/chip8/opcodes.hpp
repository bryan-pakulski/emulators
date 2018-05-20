// This file contains function definitions for the cpu

#ifndef __OPCODES_HPP__
#define __OPCODES_HPP__

#include "cpu.hpp"

// Forward declaration
class cpu;

class opcode
{

public:
	explicit opcode( cpu *p );
	~opcode();

	// See wikipedia for list of opcode instructions
	void op0NNN();
	void op0EE0();
	void opEE00();

private:
	// Opcodes need access to memory and other values that the cpu uses
	cpu *proc;
};

#endif