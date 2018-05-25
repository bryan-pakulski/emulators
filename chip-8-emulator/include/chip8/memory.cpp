#include "memory.hpp"

memory::memory()
{
	// Load fontset
	for ( int i = 0; i < 80; i++ )
		set( i, chip8_fontset[i] );

	std::cerr << "Initialised fontset" << std::endl;
}

memory::~memory()
{
	
}

/**
 * @brief      Gets the value of memory at the given index
 *
 * @param[in]  index  The index
 *
 * @return     returns char value of memory (one half of an instruction)
 */
unsigned char memory::get(int index)
{
	// TODO: add error handler for indexes out of range
	return mem[index];
}

/**
 * @brief      Set a value in memory space
 *
 * @param[in]  index  The index
 * @param[in]  value  The value
 */
void memory::set(int index, unsigned char value)
{
	mem[index] = value;
}