#include "memoryc8.hpp"

/**
 * Initialise memory space, load fontset
 */
memoryc8::memoryc8() {
	// Load fontset
	for ( int i = 0; i < 80; i++ )
		set( i, chip8_fontset[i] );

	std::cerr << "Initialised fontset" << std::endl;
}

memoryc8::~memoryc8() {

}

/**
 * Getter at index
 *
 * @param index 
 * 
 * @return unsigned short at memory location
 */
unsigned char memoryc8::get(int index) {
	return mem[index];
}

/**
 * Setter at index
 *
 * @param index
 * @param value 
 */
void memoryc8::set(int index, unsigned char value) {
	mem[index] = value;
}