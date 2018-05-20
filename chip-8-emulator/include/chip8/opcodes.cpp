#include "opcodes.hpp"

using namespace std;

opcode::opcode( cpu *p ) : proc(p)
{
	// Initialise opcode map
	// Yay for long initialisations
	oplist.insert( pair< int, void* >( 0, (void*) &op0NNN ) );
	oplist.insert( pair< int, void* >( 1, (void*) &op00E0 ) );
	oplist.insert( pair< int, void* >( 2, (void*) &op00EE ) );
	oplist.insert( pair< int, void* >( 3, (void*) &op1NNN ) );
	oplist.insert( pair< int, void* >( 4, (void*) &op2NNN ) );

	oplist.insert( pair< int, void* >( 5, (void*) &op3XNN ) );

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