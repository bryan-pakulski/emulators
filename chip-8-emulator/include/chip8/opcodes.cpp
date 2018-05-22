#include "opcodes.hpp"

using namespace std;

opcode::opcode( cpu *p ) : proc(p)
{
	
}

opcode::~opcode()
{

}

/**
 * @brief      Executes a function from the hashtable at a given index
 *
 * @param[in]  o     opcode
 */
void opcode::execute( unsigned short o )
{

}


/**
 * @brief      Calls RCA 1802 program at address NNN.
 * 						 Not necessary for most ROMs
 */
void opcode::op0NNN()
{

}

/**
 * @brief      Clears the screen
 */
void opcode::op00E0()
{

}

/**
 * @brief      Returns from a subroutine
 */
void opcode::op00EE()
{

}

/**
 * @brief      Jumps to address NNN
 */
void opcode::op1NNN()
{

}

/**
 * @brief      Calls subroutine at NNN
 */
void opcode::op2NNN()
{

}



/**
 * @brief      Skips the next instruction if VX equals NN
 */
void opcode::op3XNN()
{

}

/**
 * @brief      Skips the next instruction if VX doesn't equal NN
 */
void opcode::op4XNN()
{

}

/**
 * @brief      Skips the next instruction if VX equals VY
 */
void opcode::op5XY0()
{

}

/**
 * @brief      Sets VX to NN
 */
void opcode::op6XNN()
{

}

/**
 * @brief      Adds NN to VX
 */
void opcode::op7XNN()
{

}



/**
 * @brief      Sets VX to the value of VY
 */
void opcode::op8XY0()
{

}

/**
 * @brief      Sets VX to VX or VY
 */
void opcode::op8XY1()
{

}

/**
 * @brief      Sets VX to VX and VY
 */
void opcode::op8XY2()
{

}

/**
 * @brief      Sets VX to VX xor VY
 */
void opcode::op8XY3()
{

}

/**
 * @brief     Adds VY to VX. VF is set to 1 when there's a carry,
 * 						and to 0 when there isn't
 */
void opcode::op8XY4()
{

}



/**
 * @brief      VY is subtracted from VX. VF is set to 0 when there's a 
 * 						 borrow, and 1 when there isn't
 */
void opcode::op8XY5()
{

}

/**
 * @brief      Shifts VX right by one. VF is set to the value
 * 						 of the least significant bit of VX before the shift
 */
void opcode::op8XY6()
{

}

/**
 * @brief      Sets VX to VY minus VX. VF is set to 0 when there's a borrow,
 * 						 and 1 when there isn't
 */
void opcode::op8XY7()
{

}

/**
 * @brief      Shifts VX left by one.VF is set to the value of the
 * 						 most significant bit of VX before the shift
 */
void opcode::op8XYE()
{

}

/**
 * @brief      Skips the next instruction if VX doesn't equal VY
 */
void opcode::op9XY0()
{

}



/**
 * @brief      Sets I to the address NNN
 */
void opcode::opANNN()
{
	proc->setI( proc->getOP() & 0xFFF );
	proc->setPC( proc->getPC() + 2 );
}

/**
 * @brief      Jumps to the address NNN plus V0
 */
void opcode::opBNNN()
{

}

/**
 * @brief      Sets VX to the result of a bitwise and
 * 						 operation on a random number and NN
 */
void opcode::opCXNN()
{

}

/**
 * @brief      Sprites stored in memory at location in index register (I),
 *						 8bits wide. Wraps around the screen. If when 
 *						 drawn, clears a pixel, register VF is set to 1 otherwise it is
 *						 zero. All drawing is XOR drawing
 *						 (i.e. it toggles the screen pixels). Sprites are drawn starting
 *						 at position VX, VY. N is the number of 8bit rowsthat need to be
 *						 drawn. If N is greater than 1, second line continues at position
 *						 VX, VY+1, and so on
 */
void opcode::opDXYN()
{

}

/**
 * @brief      Skips the next instruction if the key stored in VX is pressed
 */
void opcode::opEX9E()
{

}



/**
 * @brief      Skips the next instruction if the key stored in VX isn't pressed
 */
void opcode::opEXA1()
{

}

/**
 * @brief      Sets VX to the value of the delay timer
 */
void opcode::opFX07()
{

}

/**
 * @brief      A key press is awaited, and then stored in VX
 */
void opcode::opFX0A()
{

}

/**
 * @brief      Sets the delay timer to VX
 */
void opcode::opFX15()
{

}

/**
 * @brief      Sets the sound timer to VX
 */
void opcode::opFX18()
{

}



/**
 * @brief      Adds VX to I
 */
void opcode::opFX1E()
{

}

/**
 * @brief      Sets I to the location of the sprite for the character in VX.
 *  					 Characters 0-F (in hexadecimal) are represented by a 4x5 font
 */
void opcode::opFX29()
{

}

/**
 * @brief      Stores the Binary-coded decimalrepresentation of VX,
 * 						 with the most significant of three digits at the address in I,
 * 						 the middle digit at I plus 1, and the least significant digit at
 * 						 I plus 2. (In other words, take the decimalrepresentation of VX,
 * 						 place the hundreds digit in memory at location in I,
 * 						 the tens digit at location I+1,
 * 						 and the ones digit at location I+2)
 */
void opcode::opFX33()
{

}

/**
 * @brief      Stores V0 to VX in memory starting at address I
 */
void opcode::opFX55()
{

}

/**
 * @brief      Fills V0 to VX with values from memory starting at address I
 */
void opcode::opFX65()
{

}