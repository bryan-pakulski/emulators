#include "chip8.h"
#include "cpu/cpu.h"
#include "globals.h"
#include "memoryc8/memoryc8.h"

#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <SDL2/SDL_keycode.h>

chip8::chip8() {
  mem = new memoryc8();
  proc = new cpu(mem);
  cpuScheduler = new taskScheduler<cpuCycle, cpu *>(CLOCK_SPEED);
}

chip8::~chip8() {
  delete proc;
  delete mem;
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
      proc->drawFlag = false;
    }

    if (proc->clearScreen) {
      proc->clearScreen = false;
    }

    // INPUT
    // TODO: input loop

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
bool chip8::loadRomIntoMemory(char *filePath) {
  // Load into buffer
  std::cerr << "Loading game: " << filePath << std::endl;
  std::ifstream game(filePath, std::ios::binary);

  std::vector<unsigned char> game_buffer =
      std::vector<unsigned char>((std::istreambuf_iterator<char>(game)), (std::istreambuf_iterator<char>()));
  game.close();

  if (game_buffer.size() > MAX_GAMESIZE) {
    std::cerr << "Error; maximum game size exceeded"
              << "Current limit is: " << MAX_GAMESIZE << " bytes" << std::endl;
    return false;
  } else {
    std::cerr << "Game loaded successfully into buffer, moving to memory.." << std::endl;
    int index = 0x200;
    for (unsigned char value : game_buffer) {
      mem->set(index, value);

      index++;
    }
    std::cerr << "Successfully loaded game into memory..." << std::endl;
  }

  return true;
}

template class taskScheduler<cpuCycle, cpu *>;