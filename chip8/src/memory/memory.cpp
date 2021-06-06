#include "memory.hpp"

/**
 * Initialise memory space, load fontset
 */
memory::memory() {
	// Load fontset
	for ( int i = 0; i < 80; i++ )
		set( i, chip8_fontset[i] );

	std::cerr << "Initialised fontset" << std::endl;
}

memory::~memory() {

}

/**
 * Getter at index
 *
 * @param index 
 * 
 * @return unsigned short at memory location
 */
unsigned char memory::get(int index) {
	return mem[index];
}

/**
 * Setter at index
 *
 * @param index
 * @param value 
 */
void memory::set(int index, unsigned char value) {
	mem[index] = value;
}