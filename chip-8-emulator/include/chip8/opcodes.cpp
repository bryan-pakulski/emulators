#include "opcodes.hpp"

using namespace std;

opcode::opcode( cpu *p ) : proc(p)
{
	// Initialise opcode map
	// Yay for long initialisations
	/*
	oplist.insert( pair< int, void* >( 0, (void*) &op0NNN ) );
	oplist.insert( pair< int, void* >( 1, (void*) &op00E0 ) );
	oplist.insert( pair< int, void* >( 2, (void*) &op00EE ) );
	oplist.insert( pair< int, void* >( 3, (void*) &op1NNN ) );
	oplist.insert( pair< int, void* >( 4, (void*) &op2NNN ) );

	oplist.insert( pair< int, void* >( 5, (void*) &op3XNN ) );
	oplist.insert( pair< int, void* >( 6, (void*) &op4XNN ) );
	oplist.insert( pair< int, void* >( 7, (void*) &op5XY0 ) );
	oplist.insert( pair< int, void* >( 8, (void*) &op6XNN ) );
	oplist.insert( pair< int, void* >( 9, (void*) &op7XNN ) );

	oplist.insert( pair< int, void* >( 10, (void*) &op ) );
	oplist.insert( pair< int, void* >( 11, (void*) &op ) );
	oplist.insert( pair< int, void* >( 12, (void*) &op ) );
	oplist.insert( pair< int, void* >( 13, (void*) &op ) );
	oplist.insert( pair< int, void* >( 14, (void*) &op ) );
	*/
	


}

opcode::~opcode()
{

}

void opcode::op0NNN()
{

}

void opcode::op00E0()
{

}

void opcode::op00EE()
{

}

void opcode::op1NNN()
{

}

void opcode::op2NNN()
{

}

void opcode::op3XNN()
{

}

void opcode::op4XNN()
{

}

void opcode::op5XY0()
{

}

void opcode::op6XNN()
{

}

void opcode::op7XNN()
{

}