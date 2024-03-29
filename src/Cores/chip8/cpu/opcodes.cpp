#include <iostream>
#include <stdexcept>

#include "globals.h"
#include "opcodes.h"

using namespace std;

opcodes::opcodes() { std::map<unsigned short, int> optable; }

opcodes::~opcodes() {}

/**
 * Gets function from the hashtable at a given index - If the function has not yet
 * been added to the lookup table it is inserted here with the key of the opcode
 * that has called it
 *
 * @param o opcode
 */
func_p opcodes::get(unsigned short o) {
  // Check if instruction already exists in opcode lookup table
  // If not then decode instruction based on HPP header and add to lookup
  int instruction = lookup(o);

  if (instruction == -1) {
    instruction = decode(o);

    if (instruction != -1) {
      cerr << "Inserting new opcode: " << std::hex << o << " with key: " << std::hex << instruction << endl;
      optable.insert(std::pair<unsigned short, int>(o, instruction));
    } else {
      throw std::runtime_error("Invalid opcode: " + to_string(o));
    }
  }

  // Run instruction from opcode lookup table, passes along current opcode operation
  return oplist[instruction];
}

/**
 * Checks if an instruction already exists in the optable
 * If not it will be decoded and added for faster lookup next time
 *
 * @param o Opcode
 *
 * @return Returns the index location of function to call
 */
int opcodes::lookup(unsigned short o) {
  // Find in optable
  auto search = optable.find(o);

  if (search != optable.end())
    return search->second;
  else
    return -1;
}

/**
 * Decodes a given opcode and returns an index
 *
 * @param o Opcode
 *
 * @return Returns the index location lookup key of the function to call
 */
int opcodes::decode(unsigned short o) {
  cerr << "Parsing new opcode: " << std::hex << o << endl;
  switch (o & 0xF000) {
  case 0x0000:
    switch (o & 0x0F00) {
    case 0x0000:
      switch (o & 0x000F) {
      case 0x0000:
        return 1;
        break;

      case 0x000E:
        return 2;
        break;
      }
      break;

    default:
      return 0;
    }
    break;

  case 0x1000:
    return 3;
    break;

  case 0x2000:
    return 4;
    break;

  case 0x3000:
    return 5;
    break;

  case 0x4000:
    return 6;
    break;

  case 0x5000:
    return 7;
    break;

  case 0x6000:
    return 8;
    break;

  case 0x7000:
    return 9;
    break;

  case 0x8000:
    switch (o & 0x000F) {
    case 0x0000:
      return 10;
      break;

    case 0x0001:
      return 11;
      break;

    case 0x0002:
      return 12;
      break;

    case 0x0003:
      return 13;
      break;

    case 0x0004:
      return 14;
      break;

    case 0x0005:
      return 15;
      break;

    case 0x0006:
      return 16;
      break;

    case 0x0007:
      return 17;
      break;

    case 0x000E:
      return 18;
      break;
    }
    break;

  case 0x9000:
    return 19;
    break;

  case 0xA000:
    return 20;
    break;

  case 0xB000:
    return 21;
    break;

  case 0xC000:
    return 22;
    break;

  case 0xD000:
    return 23;
    break;

  case 0xE000:
    switch (o & 0x00FF) {
    case 0x009E:
      return 24;
      break;

    case 0x00A1:
      return 25;
      break;
    }
    break;

  case 0xF000:
    switch (o & 0x00FF) {
    case 0x0007:
      return 26;
      break;

    case 0x000A:
      return 27;
      break;

    case 0x0015:
      return 28;
      break;

    case 0x0018:
      return 29;
      break;

    case 0x001E:
      return 30;
      break;

    case 0x0029:
      return 31;
      break;

    case 0x0033:
      return 32;
      break;

    case 0x0055:
      return 33;
      break;

    case 0x0065:
      return 34;
      break;
    }
    break;
  }

  cerr << "Unknown opcode encountered: " << o << endl;
  return -1;
}

/**
 * @brief      Calls RCA 1802 program at address NNN.
 * 						 Not necessary for most ROMs
 */
void opcodes::op0NNN(cpu *proc) {}

/**
 * @brief      Clears the screen
 */
void opcodes::op00E0(cpu *proc) { proc->clearScreen = true; }

/**
 * Returns from a subroutine
 */
void opcodes::op00EE(cpu *proc) { proc->setPC(proc->popStack()); }

/**
 * Jumps to address NNN
 */
void opcodes::op1NNN(cpu *proc) { proc->setPC(proc->getOP() & 0x0FFF); }

/**
 * Calls subroutine at NNN
 */
void opcodes::op2NNN(cpu *proc) {
  proc->pushStack(proc->getPC());
  proc->setPC(proc->getOP() & 0x0FFF);
}

/**
 * Skips the next instruction if VX equals NN
 */
void opcodes::op3XNN(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;
  unsigned short n = (proc->getOP() & 0x00FF);

  if (proc->getV(x) == n) {
    proc->stepPC(1);
  }
}

/**
 * Skips the next instruction if VX doesn't equal NN
 */
void opcodes::op4XNN(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;
  unsigned short n = (proc->getOP() & 0x00FF);

  if (proc->getV(x) != n) {
    proc->stepPC(1);
  }
}

/**
 * Skips the next instruction if VX equals VY
 */
void opcodes::op5XY0(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;
  unsigned short y = (proc->getOP() & 0x00F0) >> 4;

  if (proc->getV(x) == proc->getV(y)) {
    proc->stepPC(1);
  }
}

/**
 * Sets VX to NN
 */
void opcodes::op6XNN(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;
  unsigned short n = (proc->getOP() & 0x00FF);

  proc->setV(x, n);
}

/**
 * Adds NN to VX
 */
void opcodes::op7XNN(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;
  unsigned short n = (proc->getOP() & 0x00FF);

  proc->setV(x, proc->getV(x) + n);
}

/**
 * Sets VX to the value of VY
 */
void opcodes::op8XY0(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;
  unsigned short y = (proc->getOP() & 0x00F0) >> 4;

  proc->setV(x, proc->getV(y));
}

/**
 * Sets VX to VX or VY
 */
void opcodes::op8XY1(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;
  unsigned short y = (proc->getOP() & 0x00F0) >> 4;

  proc->setV(x, proc->getV(x) | proc->getV(y));
}

/**
 * Sets VX to VX and VY
 */
void opcodes::op8XY2(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;
  unsigned short y = (proc->getOP() & 0x00F0) >> 4;

  proc->setV(x, proc->getV(x) & proc->getV(y));
}

/**
 * Sets VX to VX xor VY
 */
void opcodes::op8XY3(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;
  unsigned short y = (proc->getOP() & 0x00F0) >> 4;

  proc->setV(x, proc->getV(x) ^ proc->getV(y));
}

/**
 * Adds VY to VX. VF is set to 1 when there's a carry,
 * and to 0 when there isn't
 */
void opcodes::op8XY4(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;
  unsigned short y = (proc->getOP() & 0x00F0) >> 4;

  short sum = proc->getV(x) + proc->getV(y);

  if (sum > 0xFF) {
    proc->setV(0xF, 1);
    sum -= 0x100;
  }

  proc->setV(x, sum);
}

/**
 * VY is subtracted from VX. VF is set to 0 when there's a
 * borrow, and 1 when there isn't
 */
void opcodes::op8XY5(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;
  unsigned short y = (proc->getOP() & 0x00F0) >> 4;

  short diff = proc->getV(x) - proc->getV(y);
  proc->setV(0xF, 1);

  if (diff < 0) {
    proc->setV(0xF, 0);
    diff += 0x100;
  }

  proc->setV(x, diff);
}

/**
 * Shifts VX right by one. VF is set to the value
 * of the least significant bit of VX before the shift
 */
void opcodes::op8XY6(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;

  // Get least significant bit
  proc->setV(0xF, proc->getV(x) & 0x1);
  proc->setV(x, proc->getV(x) >> 1);
}

/**
 * Sets VX to VY minus VX. VF is set to 0 when there's a borrow,
 * and 1 when there isn't
 */
void opcodes::op8XY7(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;
  unsigned short y = (proc->getOP() & 0x00F0) >> 4;

  short diff = proc->getV(y) - proc->getV(x);

  proc->setV(0xF, 1);

  if (diff < 0) {
    proc->setV(0xF, 0);
    diff += 0x100;
  }

  proc->setV(x, diff);
}

/**
 * Shifts VX left by one.VF is set to the value of the
 * most significant bit of VX before the shift
 */
void opcodes::op8XYE(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;

  proc->setV(0xF, proc->getV(x) >> 7);
  proc->setV(x, proc->getV(x) << 1);
}

/**
 * Skips the next instruction if VX doesn't equal VY
 */
void opcodes::op9XY0(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;
  unsigned short y = (proc->getOP() & 0x00F0) >> 4;

  if (proc->getV(x) != proc->getV(y)) {
    proc->stepPC(1);
  }
}

/**
 * Sets I to the address NNN
 */
void opcodes::opANNN(cpu *proc) { proc->setI(proc->getOP() & 0x0FFF); }

/**
 * Jumps to the address NNN plus V0
 */
void opcodes::opBNNN(cpu *proc) { proc->setPC((proc->getOP() & 0x0FFF) + proc->getV(0)); }

/**
 * Sets VX to the result of a bitwise and
 * operation on a random number and NN
 */
void opcodes::opCXNN(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;
  unsigned short v_nn = proc->getOP() & 0x00FF;

  // TODO: generate random byte in the following format
  int r = ((rand() % (0xF + 1 - 0x0)) + 0x0);
  proc->setV(x, r & v_nn);
}

/**
 * Sprites stored in memory at location in index register (I),
 * 8bits wide. Wraps around the screen. If when
 * drawn, clears a pixel, register VF is set to 1 otherwise it is
 * zero. All drawing is XOR drawing (i.e. it toggles the screen pixels).
 * Sprites are drawn starting at position VX, VY. N is the number of 8bit
 * rows that need to be drawn. If N is greater than 1,
 * second line continues at position VX, VY+1, and so on
 */
void opcodes::opDXYN(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;
  unsigned short y = (proc->getOP() & 0x00F0) >> 4;
  unsigned short nRows = (proc->getOP() & 0x000F);

  proc->setV(0xF, 0);

  // Normalized coordinates
  unsigned short xPos = proc->getV(x) % c8_display::INTERNAL_WIDTH;
  unsigned short yPos = proc->getV(y) % c8_display::INTERNAL_HEIGHT;

  // Iterate over display
  for (int row = 0; row < nRows; ++row) {

    unsigned short sprite = proc->mem->get(proc->getI() + row);

    for (int col = 0; col < 8; ++col) {

      if ((sprite & (0x80 >> col)) != 0) {
        unsigned short index = ((yPos + row) * c8_display::INTERNAL_WIDTH) + (xPos + col);
        index %= (c8_display::INTERNAL_WIDTH * c8_display::INTERNAL_HEIGHT);
        // unsigned char gfxVal = proc->gfx->getPixel(index);

        // if (gfxVal == 0xF) {
        //   proc->setV(0xF, 1);
        // }

        // gfxVal ^= 0xF;
        // proc->gfx->setPixel(index, gfxVal);
      }
    }
  }

  proc->drawFlag = true;
}

/**
 * Skips the next instruction if the key stored in VX is pressed
 */
void opcodes::opEX9E(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;
  unsigned short key = proc->getV(x);

  if (proc->keyPressed(key)) {
    proc->stepPC(1);
  }
}

/**
 * Skips the next instruction if the key stored in VX isn't pressed
 */
void opcodes::opEXA1(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;
  unsigned short key = proc->getV(x);

  if (!proc->keyPressed(key)) {
    proc->stepPC(1);
  }
}

/**
 * Sets VX to the value of the delay timer
 */
void opcodes::opFX07(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;

  proc->setV(x, proc->delayTimer);
}

/**
 * A key press is awaited, and then stored in VX
 */
void opcodes::opFX0A(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;

  bool keyPressed = false;

  while (!keyPressed) {
    for (int i = 0; i < 0xF; i++) {
      if (proc->keyPressed(i)) {
        proc->setV(x, i);
        keyPressed = true;
        break;
      }
    }
  }
}

/**
 * Sets the delay timer to VX
 */
void opcodes::opFX15(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;

  proc->delayTimer = proc->getV(x);
}

/**
 * Sets the sound timer to VX
 */
void opcodes::opFX18(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;

  proc->soundTimer = proc->getV(x);
}

/**
 * Adds VX to I
 */
void opcodes::opFX1E(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;

  proc->setI(proc->getI() + proc->getV(x));
}

/**
 * Sets I to the location of the sprite for the shortacter in VX.
 * shortacters 0-F (in hexadecimal) are represented by a 4x5 font
 */
void opcodes::opFX29(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;

  proc->setI(proc->getV(x) * 5);
}

/**
 * Stores the Binary-coded decimal representation of VX,
 * with the most significant of three digits at the address in I,
 * the middle digit at I plus 1, and the least significant digit at
 * I plus 2. (In other words, take the decimal representation of VX,
 * place the hundreds digit in memory at location in I,
 * the tens digit at location I+1,
 * and the ones digit at location I+2)
 */
void opcodes::opFX33(cpu *proc) {

  unsigned short x = (proc->getOP() & 0x0F00) >> 8;
  unsigned short vx = proc->getV(x);

  for (int i = 2; i >= 0; i--) {
    proc->mem->set(proc->getI() + i, vx % 10);
    vx /= 10;
  }
}

/**
 * Stores V0 to VX in memory starting at address I
 */
void opcodes::opFX55(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;

  for (int i = 0; i <= x; ++i) {
    proc->mem->set(proc->getI() + i, proc->getV(i));
  }
}

/**
 * Fills V0 to VX with values from memory starting at address I
 */
void opcodes::opFX65(cpu *proc) {
  unsigned short x = (proc->getOP() & 0x0F00) >> 8;

  for (int i = 0; i <= x; ++i) {
    proc->setV(i, proc->mem->get(proc->getI() + i));
  }
}