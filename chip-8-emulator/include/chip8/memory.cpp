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

/**
 * @brief		Dumps memory to a human readable text file
 */
void memory::dump_memory()
{
	std::cerr << "Dumping memory to path: bin/mem_dump" << std::endl; 
	std::ofstream mem_dump("bin/mem_dump", std::ios::binary );

	for (unsigned char i : mem)
	{
		mem_dump << std::hex << i;
	}

	mem_dump.close();
}