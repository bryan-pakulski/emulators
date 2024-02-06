#pragma once
#include <iostream>

#include "memoryc8/memoryc8.h"
#include "opcodes.h"

class opcodes;
class display;

class cpu {
private:
  opcodes *op_lookup;

  unsigned short V[16]{0};     // CPU registers, 16th is carry flag
  unsigned short I;            // Index register
  unsigned short PC;           // Program counter 0x000 -> 0xFFF
  unsigned short op;           // Current opcode
  unsigned short stack[16]{0}; // Stack implementation
  unsigned short sp;           // Stack pointer
  unsigned char keypad[16]{0}; // keypad input 0x0 -> 0xF, value is 1 if pressed

public:
  cpu(memoryc8 *m);
  ~cpu();

  // Public flags
  bool drawFlag;
  bool clearScreen;
  unsigned short delayTimer = 0x0;
  unsigned short soundTimer = 0x0;

  memoryc8 *mem;

  // Getter and setter functions
  unsigned short getI();
  void setI(unsigned short value);

  unsigned short getPC();
  void stepPC(int value);
  void setPC(unsigned short value);

  unsigned short getOP();
  void setOP(unsigned short value);

  unsigned short getV(int index);
  void setV(int index, unsigned short value);

  unsigned short popStack();
  void pushStack(unsigned short value);

  unsigned short fetchNextOpcode(); // Fetch next opcode from memory

  void clearKeyPad();
  void setKey(int index, unsigned char value);
  bool keyPressed(int index);

  static void cycle(cpu *);
};