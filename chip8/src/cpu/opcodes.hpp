#ifndef __OPCODES8_HPP__
#define __OPCODES8_HPP__

#include "cpu.hpp"
#include <map>

// Forward declaration
class cpu;

typedef void(*func_p)(unsigned short, cpu*);

class opcodes {

	private:
		int lookup( unsigned short );

		std::map< int, void(opcodes::*)(unsigned short, cpu*) > oplist = {
		{ 0,  &opcodes::op0NNN }, { 1,  &opcodes::op00E0 }, { 2,  &opcodes::op00EE },
		{ 3,  &opcodes::op1NNN }, { 4,  &opcodes::op2NNN },

		{ 5,  &opcodes::op3XNN }, { 6,  &opcodes::op4XNN }, { 7,  &opcodes::op5XY0 },
		{ 8,  &opcodes::op6XNN }, { 9,  &opcodes::op7XNN },

		{ 10,  &opcodes::op8XY0 }, { 11,  &opcodes::op8XY1 }, { 12,  &opcodes::op8XY2 },
		{ 13,  &opcodes::op8XY3 }, { 14,  &opcodes::op8XY4 },

		{ 15,  &opcodes::op8XY5 }, { 16,  &opcodes::op8XY6 }, { 17,  &opcodes::op8XY7 },
		{ 18,  &opcodes::op8XYE }, { 19,  &opcodes::op9XY0 },

		{ 20,  &opcodes::opANNN }, { 21,  &opcodes::opBNNN }, { 22,  &opcodes::opCXNN },
		{ 23,  &opcodes::opDXYN }, { 24,  &opcodes::opEX9E },

		{ 25,  &opcodes::opEXA1 }, { 26,  &opcodes::opFX07 }, { 27,  &opcodes::opFX0A },
		{ 28,  &opcodes::opFX15 }, { 29,  &opcodes::opFX18 },

		{ 30,  &opcodes::opFX1E }, { 31,  &opcodes::opFX29 }, { 32,  &opcodes::opFX33 },
		{ 33,  &opcodes::opFX55 }, { 34,  &opcodes::opFX65 }
	};

	// This gets populated during runtime with opcodes, a hashtable is built so that
	// the most used opcodes don't have to be decoded i.e. main game loop
	std::map< unsigned short, int > optable;
	int decode( unsigned short );

	// See wikipedia for list of opcode instructions
	void op0NNN(unsigned short, cpu*);
	void op00E0(unsigned short, cpu*);
	void op00EE(unsigned short, cpu*);
	void op1NNN(unsigned short, cpu*);
	void op2NNN(unsigned short, cpu*);

	void op3XNN(unsigned short, cpu*);
	void op4XNN(unsigned short, cpu*);
	void op5XY0(unsigned short, cpu*);
	void op6XNN(unsigned short, cpu*);
	void op7XNN(unsigned short, cpu*);

	void op8XY0(unsigned short, cpu*);
	void op8XY1(unsigned short, cpu*);
	void op8XY2(unsigned short, cpu*);
	void op8XY3(unsigned short, cpu*);
	void op8XY4(unsigned short, cpu*);

	void op8XY5(unsigned short, cpu*);
	void op8XY6(unsigned short, cpu*);
	void op8XY7(unsigned short, cpu*);
	void op8XYE(unsigned short, cpu*);
	void op9XY0(unsigned short, cpu*);

	void opANNN(unsigned short, cpu*);
	void opBNNN(unsigned short, cpu*);
	void opCXNN(unsigned short, cpu*);
	void opDXYN(unsigned short, cpu*);
	void opEX9E(unsigned short, cpu*);

	void opEXA1(unsigned short, cpu*);
	void opFX07(unsigned short, cpu*);
	void opFX0A(unsigned short, cpu*);
	void opFX15(unsigned short, cpu*);
	void opFX18(unsigned short, cpu*);

	void opFX1E(unsigned short, cpu*);
	void opFX29(unsigned short, cpu*);
	void opFX33(unsigned short, cpu*);
	void opFX55(unsigned short, cpu*);
	void opFX65(unsigned short, cpu*);

	public:
		opcodes();
		~opcodes();

		func_p get(unsigned short o);

		
};

#endif