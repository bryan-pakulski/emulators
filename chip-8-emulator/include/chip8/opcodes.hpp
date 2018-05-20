// This file contains function definitions for the cpu

#ifndef __OPCODES_HPP__
#define __OPCODES_HPP__

#include "cpu.hpp"
#include <map>
#include <string>

// Forward declaration
class cpu;

class opcode
{

public:
	explicit opcode( cpu *p );
	~opcode();

private:
	// Opcodes class need access to memory and other values that the cpu uses
	// This is done via this class pointer
	cpu *proc;

	const std::map< int , void* > oplist = {
		{ 0, (void*) &op0NNN }, { 1, (void*) &op00E0 }, { 2, (void*) &op00EE },
		{ 3, (void*) &op1NNN }, { 4, (void*) &op1NNN },

		{ 4, (void*) &op3XNN }, { 6, (void*) &op4XNN }, { 7, (void*) &op5XY0 },
		{ 8, (void*) &op6XNN }, { 9, (void*) &op7XNN },

		{ 10, (void*) &op8XY0 }, { 11, (void*) &op8XY1 }, { 12, (void*) &op8XY2 },
		{ 13, (void*) &op8XY3 }, { 14, (void*) &op8XY4 },

		{ 15, (void*) &op8XY5 }, { 16, (void*) &op8XY6 }, { 17, (void*) &op8XY7 },
		{ 18, (void*) &op8XYE }, { 19, (void*) &op9XY0 },

		{ 20, (void*) &opANNN }, { 21, (void*) &opBNNN }, { 22, (void*) &opCXNN },
		{ 23, (void*) &opDXYN }, { 24, (void*) &opEX9E },

		{ 25, (void*) &opEXA1 }, { 26, (void*) &opFX07 }, { 27, (void*) &opFX0A },
		{ 28, (void*) &opFX15 }, { 29, (void*) &opFX18 },

		{ 30, (void*) &opFX1E }, { 31, (void*) &opFX29 }, { 32, (void*) &opFX33 },
		{ 33, (void*) &opFX55 }, { 34, (void*) &opFX65 }
	};

	// See wikipedia for list of opcode instructions
	static void op0NNN();
	static void op00E0();
	static void op00EE();
	static void op1NNN();
	static void op2NNN();

	static void op3XNN();
	static void op4XNN();
	static void op5XY0();
	static void op6XNN();
	static void op7XNN();

	static void op8XY0();
	static void op8XY1();
	static void op8XY2();
	static void op8XY3();
	static void op8XY4();

	static void op8XY5();
	static void op8XY6();
	static void op8XY7();
	static void op8XYE();
	static void op9XY0();

	static void opANNN();
	static void opBNNN();
	static void opCXNN();
	static void opDXYN();
	static void opEX9E();

	static void opEXA1();
	static void opFX07();
	static void opFX0A();
	static void opFX15();
	static void opFX18();

	static void opFX1E();
	static void opFX29();
	static void opFX33();
	static void opFX55();
	static void opFX65();

};

#endif