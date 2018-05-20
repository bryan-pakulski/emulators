#include "memory.hpp"

memory::memory()
{

}

memory::~memory()
{
	
}

unsigned char memory::get(int index)
{
	// TODO: add error handler for indexes out of range
	return mem[index];
}