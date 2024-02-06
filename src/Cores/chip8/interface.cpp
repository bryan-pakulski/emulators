#include <iostream>

#include "chip8.h"
#include "QLogger.h"

extern "C" {
bool core_init() {
  QLogger::GetInstance().Log(LOGLEVEL::INFO, "Initialising chip8 core");

  // Initialise cpu and load rom
  chip8 c8 = chip8();

  return true;
}

// Window passed to emulator, returned data is rendered by CoreLink application
void core_gui() {}

// Pass glfw input for core to process
void core_input() {}

// Load rom into memory
bool load_rom(const std::string &filepath) { return true; }
}