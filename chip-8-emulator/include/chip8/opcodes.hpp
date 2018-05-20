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

	std::map< int , void* > oplist = {
		{ 0, (void*) &op0NNN }, { 1, (void*) &op0NNN }, { 2, (void*) &op0NNN },
		{ 3, (void*) &op0NNN }, { 4, (void*) &op0NNN },

		{ 4, (void*) &op0NNN }, { 6, (void*) &op0NNN }, { 7, (void*) &op0NNN },
		{ 8, (void*) &op0NNN }, { 9, (void*) &op0NNN },

		{ 10, (void*) &op0NNN }, { 11, (void*) &op0NNN }, { 12, (void*) &op0NNN },
		{ 13, (void*) &op0NNN }, { 14, (void*) &op0NNN },

		{ 15, (void*) &op0NNN }, { 16, (void*) &op0NNN }, { 17, (void*) &op0NNN },
		{ 18, (void*) &op0NNN }, { 19, (void*) &op0NNN },

		{ 20, (void*) &op0NNN }, { 21, (void*) &op0NNN }, { 22, (void*) &op0NNN },
		{ 23, (void*) &op0NNN }, { 24, (void*) &op0NNN },

		{ 25, (void*) &op0NNN }, { 26, (void*) &op0NNN }, { 27, (void*) &op0NNN },
		{ 28, (void*) &op0NNN }, { 29, (void*) &op0NNN },

		{ 30, (void*) &op0NNN }, { 31, (void*) &op0NNN }, { 32, (void*) &op0NNN },
		{ 33, (void*) &op0NNN }, { 34, (void*) &op0NNN }
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