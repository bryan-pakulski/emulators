#include "chip8.hpp"
#include "globals.hpp"


#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <SDL2/SDL_keycode.h>

chip8::chip8() {
	mem = new memoryc8();
	gfx = new display();
	gfxDebug = new displayDebugCPU();
	proc = new cpu(mem, gfx);
	in = new inputHandler();
	cpuScheduler = new taskScheduler<cpuCycle, cpu*>(CLOCK_SPEED);
}

chip8::~chip8() {
	delete gfx;
	delete gfxDebug;
	delete proc;
	delete mem;
	delete in;
	delete cpuScheduler;
}

void chip8::gameloop() {

	bool running = true;
	cpuCycle cyclePtr = cpu::cycle;
	
	while (running) {

		// CPU
		cpuScheduler->executeCommand(cyclePtr, proc);

		// GFX
		if (proc->drawFlag) {
			gfx->doUpdate();
			proc->drawFlag = false;
		}

		if (proc->clearScreen) {
			gfx->clear();
			proc->clearScreen = false;
		}
		gfxDebug->doUpdate(proc);
		
		// INPUT
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE) {
				running = false;
				break;
			} else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
				running = false;
				break;
			}

			in->processInput(e, proc);
		}

		// SOUND
		// TODO: these need to de-increment at 60hz
		if (proc->delayTimer > 0) {
			--proc->delayTimer;
		}

		if (proc->soundTimer > 0) {
			--proc->soundTimer;
		}
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
		std::cerr << "Error; maximum game size exceeded" << "Current limit is: " << MAX_GAMESIZE << " bytes" << std::endl;
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

template class taskScheduler<cpuCycle, cpu*>;