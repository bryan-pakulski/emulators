#include "cpu.h"
#include <cstring>
#include <vector>
#include <fstream>

cpu::cpu(memoryc8 *m) {
  mem = m;
  op_lookup = new opcodes();
  drawFlag = true;
  clearScreen = true;
  I = 0;
  PC = 0x200;
  op = 0;
  sp = 0;
}

cpu::~cpu() { delete op_lookup; }

/**
 * Resets the keypad array to 0
 */
void cpu::clearKeyPad() { memset(keypad, 0, 0xF * sizeof(*keypad)); }

/**
 * Sets a key at index to be pressed
 */
void cpu::setKey(int index, unsigned char value) { keypad[index] = value; }

/**
 * Checks if a key at index is pressed
 */
bool cpu::keyPressed(int index) { return (keypad[index] == 0x1); }

/**
 * Getter and setter functions for member variables
 */
unsigned short cpu::getI() { return I; }

void cpu::setI(unsigned short value) { I = value; }

unsigned short cpu::getPC() { return PC; }

void cpu::stepPC(int value) { PC += (2 * value); }

void cpu::setPC(unsigned short value) { PC = value; }

unsigned short cpu::getOP() { return op; }

void cpu::setOP(unsigned short value) { op = value; }

unsigned short cpu::getV(int index) { return V[index]; }

void cpu::setV(int index, unsigned short value) { V[index] = value; }

/**
 * Pops from stack
 */
unsigned short cpu::popStack() {
  --sp;
  unsigned short val = stack[sp];
  stack[sp] = 0;

  return val;
}

/**
 * Pushes to stack and increments stack pointer to stop data overwriting
 *
 * @param value  The value to push
 */
void cpu::pushStack(unsigned short value) {
  stack[sp] = value;
  ++sp;
}

/**
 * Fetch next opcode
 *
 * @return Returns combined opcodes to form a single instruction
 */
unsigned short cpu::fetchNextOpcode() { return mem->get(PC) << 8 | (mem->get(PC + 1) & 0x00FF); }

/**
 * Call function mapping from opcode and update other logic i.e. timers
 */
void cpu::cycle(cpu *proc) {

  // Fetch opcode
  proc->setOP(proc->fetchNextOpcode());

  // Increment PC before execution
  proc->stepPC(1);

  // Decode opcode and execute
  func_p opCallFunction = proc->op_lookup->get(proc->getOP());
  opCallFunction(proc);
}