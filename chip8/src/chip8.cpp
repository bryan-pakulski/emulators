#include "chip8.hpp"

#include <iostream>
#include <vector>
#include <fstream>

chip8::chip8() {
	mem = new memory();
	proc = new cpu(mem);
	gfx = new display();
}

chip8::~chip8() {
	delete gfx;
	delete proc;
	delete mem;
}

void chip8::gameloop(float dt) {

	bool running = true;
	
	while (running) {
		// Process CPU cycle
		proc->cycle();

		// Update graphics
		gfx->doUpdate();

		// Get input
	}
	
}

/**
 * Loads a rom from specified path into memory space
 *
 * @param filePath path to rom
 * 
 * @return true or false whether the rom was loaded successfully
 */
bool chip8::loadRomIntoMemory(char* filePath) {
	// Load into buffer
	std::cerr << "Loading game: " << filePath << std::endl;
	std::ifstream game( filePath, std::ios::binary );

	std::vector<unsigned char> game_buffer = std::vector<unsigned char>(
		(std::istreambuf_iterator<char>(game)),
		(std::istreambuf_iterator<char>())
	);
	game.close();

	if (game_buffer.size() > MAX_GAMESIZE) {
		std:: cerr << "Error; maximum game size exceeded" <<
		"Current limit is: " << MAX_GAMESIZE << " bytes" << std::endl;
		return false;
	} else {
		std::cerr << "Game loaded successfully into buffer, moving to memory.." << std::endl;
		int index = 0x200;
		for ( unsigned char value : game_buffer )
		{
			mem->set(index, value);

			index++;
		}
		std::cerr << "Successfully loaded game into memory..." << std::endl;
	}

	return true;
}