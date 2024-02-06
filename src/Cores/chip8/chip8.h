#ifndef __CHIP8_HPP__
#define __CHIP8_HPP__

#include <iostream>

#include "cpu/taskScheduler.h"
#include "cpu/cpu.h"
#include "memoryc8/memoryc8.h"

typedef void (*cpuCycle)(cpu *);

class chip8 {
private:
  memoryc8 *mem;
  cpu *proc;
  taskScheduler<cpuCycle, cpu *> *cpuScheduler;

public:
  chip8();
  ~chip8();

  void gameloop();
  bool loadRomIntoMemory(char *filepath);
};

#endif