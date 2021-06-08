#ifndef __OPCODES8_HPP__
#define __OPCODES8_HPP__

#include "cpu.hpp"
#include <map>

class cpu;
typedef void(*func_p)(cpu*);

class opcodes {

	private:
		int lookup(unsigned short);

		std::map< int, void(*)(cpu*) > oplist = {
		{ 0,  &op0NNN }, { 1,  &op00E0 }, { 2,  &op00EE },
		{ 3,  &op1NNN }, { 4,  &op2NNN },

		{ 5,  &op3XNN }, { 6,  &op4XNN }, { 7,  &op5XY0 },
		{ 8,  &op6XNN }, { 9,  &op7XNN },

		{ 10,  &op8XY0 }, { 11,  &op8XY1 }, { 12,  &op8XY2 },
		{ 13,  &op8XY3 }, { 14,  &op8XY4 },

		{ 15,  &op8XY5 }, { 16,  &op8XY6 }, { 17,  &op8XY7 },
		{ 18,  &op8XYE }, { 19,  &op9XY0 },

		{ 20,  &opANNN }, { 21,  &opBNNN }, { 22,  &opCXNN },
		{ 23,  &opDXYN }, { 24,  &opEX9E },

		{ 25,  &opEXA1 }, { 26,  &opFX07 }, { 27,  &opFX0A },
		{ 28,  &opFX15 }, { 29,  &opFX18 },

		{ 30,  &opFX1E }, { 31,  &opFX29 }, { 32,  &opFX33 },
		{ 33,  &opFX55 }, { 34,  &opFX65 }
	};

	// This gets populated during runtime with opcodes, a hashtable is built so that
	// the most used opcodes don't have to be decoded i.e. main game loop
	std::map<unsigned short, int> optable;
	int decode(unsigned short);

	// See wikipedia for list of opcode instructions
	static void op0NNN(cpu*);
	static void op00E0(cpu*);
	static void op00EE(cpu*);
	static void op1NNN(cpu*);
	static void op2NNN(cpu*);

	static void op3XNN(cpu*);
	static void op4XNN(cpu*);
	static void op5XY0(cpu*);
	static void op6XNN(cpu*);
	static void op7XNN(cpu*);

	static void op8XY0(cpu*);
	static void op8XY1(cpu*);
	static void op8XY2(cpu*);
	static void op8XY3(cpu*);
	static void op8XY4(cpu*);

	static void op8XY5(cpu*);
	static void op8XY6(cpu*);
	static void op8XY7(cpu*);
	static void op8XYE(cpu*);
	static void op9XY0(cpu*);

	static void opANNN(cpu*);
	static void opBNNN(cpu*);
	static void opCXNN(cpu*);
	static void opDXYN(cpu*);
	static void opEX9E(cpu*);

	static void opEXA1(cpu*);
	static void opFX07(cpu*);
	static void opFX0A(cpu*);
	static void opFX15(cpu*);
	static void opFX18(cpu*);

	static void opFX1E(cpu*);
	static void opFX29(cpu*);
	static void opFX33(cpu*);
	static void opFX55(cpu*);
	static void opFX65(cpu*);

	public:
		opcodes();
		~opcodes();

		func_p get(unsigned short o);

		
};

#endif