// This file contains function definitions for the cpu

#ifndef __OPCODES_HPP__
#define __OPCODES_HPP__

#include "cpu.hpp"
#include "display.hpp"
#include <map>
#include <string>
#include <iostream>
#include <stdlib.h>

// Forward declaration
class cpu;

typedef void(*func_p)(void);

class opcode
{

public:
	explicit opcode( cpu *p );
	~opcode();

	void execute( unsigned short );
	int lookup( unsigned short );
	int decode( unsigned short );

private:
	// Opcode functions need access to memory and other values that the cpu uses
	// This is done via this class pointer
	cpu *proc;

	std::map< int, void(opcode::*)() > oplist = {
		{ 0,  &opcode::op0NNN }, { 1,  &opcode::op00E0 }, { 2,  &opcode::op00EE },
		{ 3,  &opcode::op1NNN }, { 4,  &opcode::op2NNN },

		{ 5,  &opcode::op3XNN }, { 6,  &opcode::op4XNN }, { 7,  &opcode::op5XY0 },
		{ 8,  &opcode::op6XNN }, { 9,  &opcode::op7XNN },

		{ 10,  &opcode::op8XY0 }, { 11,  &opcode::op8XY1 }, { 12,  &opcode::op8XY2 },
		{ 13,  &opcode::op8XY3 }, { 14,  &opcode::op8XY4 },

		{ 15,  &opcode::op8XY5 }, { 16,  &opcode::op8XY6 }, { 17,  &opcode::op8XY7 },
		{ 18,  &opcode::op8XYE }, { 19,  &opcode::op9XY0 },

		{ 20,  &opcode::opANNN }, { 21,  &opcode::opBNNN }, { 22,  &opcode::opCXNN },
		{ 23,  &opcode::opDXYN }, { 24,  &opcode::opEX9E },

		{ 25,  &opcode::opEXA1 }, { 26,  &opcode::opFX07 }, { 27,  &opcode::opFX0A },
		{ 28,  &opcode::opFX15 }, { 29,  &opcode::opFX18 },

		{ 30,  &opcode::opFX1E }, { 31,  &opcode::opFX29 }, { 32,  &opcode::opFX33 },
		{ 33,  &opcode::opFX55 }, { 34,  &opcode::opFX65 }
	};

	// This gets populated during runtime with opcodes, a hashtable is built so that
	// the most used opcodes don't have to be decoded i.e. main game loop
	std::map< unsigned short, int > optable = {};

	// See wikipedia for list of opcode instructions
	void op0NNN();
	void op00E0();
	void op00EE();
	void op1NNN();
	void op2NNN();

	void op3XNN();
	void op4XNN();
	void op5XY0();
	void op6XNN();
	void op7XNN();

	void op8XY0();
	void op8XY1();
	void op8XY2();
	void op8XY3();
	void op8XY4();

	void op8XY5();
	void op8XY6();
	void op8XY7();
	void op8XYE();
	void op9XY0();

	void opANNN();
	void opBNNN();
	void opCXNN();
	void opDXYN();
	void opEX9E();

	void opEXA1();
	void opFX07();
	void opFX0A();
	void opFX15();
	void opFX18();

	void opFX1E();
	void opFX29();
	void opFX33();
	void opFX55();
	void opFX65();

};

#endif