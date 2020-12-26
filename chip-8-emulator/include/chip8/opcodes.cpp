#include "opcodes.hpp"

using namespace std;

opcode::opcode( cpu *p ) : proc(p)
{

}

opcode::~opcode()
{
	delete proc;
}

/**
 * @brief      Executes a function from the hashtable at a given index
 *
 * @param[in]  o     opcode
 */
void opcode::execute( unsigned short o )
{
	// Check if instruction already exists in opcode lookup table
	// If not then decode instruction based on HPP header and add to lookup
	int instruction = lookup( o );

	if ( instruction == -1 )
	{
		instruction = decode( o );

		if ( instruction != -1 )
		{
			cerr << "Inserting new opcode: " << std::hex << o << " with key: " << std::hex << instruction << endl; 
			optable.insert( std::pair<unsigned short, int>(o, instruction) );
		}
	}

	//if (decode(o) != -1)
	//{
		auto f = oplist[instruction];
		(*this.*f)();
	//}
	
}

/**
 * @brief      checks if an instruction already exists in the optable
 *             If not it will be decoded and added for faster lookup next time
 *
 * @param[in]  o     Opcode
 *
 * @return     Returns the index location of function to call
 */
int opcode::lookup( unsigned short o )
{
	// Find in optable
	auto search = optable.find(o);

	if ( search != optable.end() )
		return search->second;
	else
		return -1;
}

/**
 * @brief      Decodes a given opcode and returns an index
 *
 * @param[in]  o     Opcode
 *
 * @return     Returns the index location of the function to call
 */
int opcode::decode( unsigned short o )
{
	cerr << "Parsing new opcode: " << o << endl;
	switch( o & 0xF000)
	{
		case 0x0000:
			switch( o & 0x0F00 )
			{
				case 0x0000:
					switch( o & 0x000F )
					{
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
			switch( o & 0x000F )
			{
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
			switch( o & 0x00FF )
			{
				case 0x009E:
					return 24;
				break;

				case 0x00A1:
					return 25;
				break;
			}
		break;

		case 0xF000:
			switch ( o & 0x00FF )
			{
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
void opcode::op0NNN()
{
	
}

/**
 * @brief      Clears the screen
 */
void opcode::op00E0()
{
	proc->clearScreen = true;
	proc->incrementPC(1);
}

/**
 * @brief      Returns from a subroutine
 */
void opcode::op00EE()
{
	proc->setPC(proc->popStack());
}

/**
 * @brief      Jumps to address NNN
 */
void opcode::op1NNN()
{
	proc->setPC( proc->getOP() & 0x0FFF );
}

/**
 * @brief      Calls subroutine at NNN
 */
void opcode::op2NNN()
{
	proc->pushStack( proc->getPC() );
	proc->setPC( proc->getOP() & 0x0FFF );
}



/**
 * @brief      Skips the next instruction if VX equals NN
 */
void opcode::op3XNN()
{
	int x = (int) (proc->getOP() & 0x0F00);
	int n = (int) (proc->getOP() & 0x00FF);

	if ( proc->getV( x ) == n )
		proc->incrementPC(2);
	else
		proc->incrementPC(1);
}

/**
 * @brief      Skips the next instruction if VX doesn't equal NN
 */
void opcode::op4XNN()
{
	int x = (int) (proc->getOP() & 0x0F00);
	int n = (int) (proc->getOP() & 0x00FF);

	if ( proc->getV( x ) != n )
		proc->incrementPC(2);
	else
		proc->incrementPC(1);
}

/**
 * @brief      Skips the next instruction if VX equals VY
 */
void opcode::op5XY0()
{
	int x = (int) (proc->getOP() & 0x0F00);
	int y = (int) (proc->getOP() & 0x00F0);

	if ( proc->getV(x) == proc->getV(y) )
		proc->incrementPC(2);
	else
		proc->incrementPC(1);
}

/**
 * @brief      Sets VX to NN
 */
void opcode::op6XNN()
{
	int x = (int) (proc->getOP() & 0x0F00);
	unsigned char n = (proc->getOP() & 0x00FF);

	proc->setV(x, n);
	proc->incrementPC(1);
}

/**
 * @brief      Adds NN to VX
 */
void opcode::op7XNN()
{
	int x = (int) (proc->getOP() & 0x0F00);
	unsigned char n = (proc->getOP() & 0x00FF);

	proc->setV( x, ( proc->getV(x) + n ) );
	proc->incrementPC(1);
}



/**
 * @brief      Sets VX to the value of VY
 */
void opcode::op8XY0()
{
	int x = (int) (proc->getOP() & 0x0F00);
	int y = (int) (proc->getOP() & 0x00F0);

	proc->setV( x, proc->getV( y ) );
	proc->incrementPC(1);
}

/**
 * @brief      Sets VX to VX or VY
 */
void opcode::op8XY1()
{
	int x = (int) (proc->getOP() & 0x0F00);
	int y = (int) (proc->getOP() & 0x00F0);

	proc->setV( x, ( proc->getV(x) | proc->getV(y) ) );
	proc->incrementPC(1);
}

/**
 * @brief      Sets VX to VX and VY
 */
void opcode::op8XY2()
{
	int x = (int) (proc->getOP() & 0x0F00);
	int y = (int) (proc->getOP() & 0x00F0);

	proc->setV( x, ( proc->getV(x) & proc->getV(y) ) );
	proc->incrementPC(1);
}

/**
 * @brief      Sets VX to VX xor VY
 */
void opcode::op8XY3()
{
	int x = (int) (proc->getOP() & 0x0F00);
	int y = (int) (proc->getOP() & 0x00F0);

	proc->setV( x, ( proc->getV(x) ^ proc->getV(y) ) );
	proc->incrementPC(1);
}

/**
 * @brief     Adds VY to VX. VF is set to 1 when there's a carry,
 * 						and to 0 when there isn't
 */
void opcode::op8XY4()
{
	// Get X, Y values and shift right
	int x = (int) (proc->getOP() & 0x0F00) >> 8;
	int y = (int) (proc->getOP() & 0x00F0) >> 4;

	uint16_t sum = proc->getV(x) + proc->getV(y);

	if (sum > 0xFF)
		proc->setV(0xF, 1);
	else
		proc->setV(0xF, 0);

	proc->setV(x, sum & 0xFF);
	proc->incrementPC(1);
}



/**
 * @brief      VY is subtracted from VX. VF is set to 0 when there's a 
 * 						 borrow, and 1 when there isn't
 */
void opcode::op8XY5()
{
	// Get X, Y values and shift right
	int x = (int) (proc->getOP() & 0x0F00) >> 8;
	int y = (int) (proc->getOP() & 0x00F0) >> 4;

	if (proc->getV(x) > proc->getV(y))
		proc->setV(0xF, 1);
	else
		proc->setV(0xF, 0);

	proc->setV(x, proc->getV(x) - proc->getV(y));
	proc->incrementPC(1);

}

/**
 * @brief      Shifts VX right by one. VF is set to the value
 * 						 of the least significant bit of VX before the shift
 */
void opcode::op8XY6()
{
	uint8_t x = (proc->getOP() & 0x0F00) >> 8;

	// Get least significant bit
	proc->setV(0xF, proc->getV(x) & 0x1);
	proc->setV(x, proc->getV(x) >> 1);
	proc->incrementPC(1);

}

/**
 * @brief      Sets VX to VY minus VX. VF is set to 0 when there's a borrow,
 * 						 and 1 when there isn't
 */
void opcode::op8XY7()
{
	uint8_t x = (proc->getOP() & 0x0F00) >> 8;
	uint8_t y = (proc->getOP() & 0x00F0) >> 4;
	
	if (proc->getV(y) > proc->getV(x))
		proc->setV(0xF, 0);
	else
		proc->setV(0xF, 1);

	proc->setV(x, proc->getV(y) - proc->getV(x));
	proc->incrementPC(1);

}

/**
 * @brief      Shifts VX left by one.VF is set to the value of the
 * 						 most significant bit of VX before the shift
 */
void opcode::op8XYE()
{
	proc->incrementPC(1);
}

/**
 * @brief      Skips the next instruction if VX doesn't equal VY
 */
void opcode::op9XY0()
{
	int x = (int) ( proc->getOP() & 0x0F00 );
	int y = (int) ( proc->getOP() & 0x00F0 );

	if ( proc->getV(x) != proc->getV(y) )
		proc->incrementPC(2);
	else
		proc->incrementPC(1);
}



/**
 * @brief      Sets I to the address NNN
 */
void opcode::opANNN()
{
	proc->setI( proc->getOP() & 0x0FFF );
	proc->incrementPC(1);
}

/**
 * @brief      Jumps to the address NNN plus V0
 */
void opcode::opBNNN()
{
	proc->setPC( (proc->getOP() & 0x0FFF) + proc->getV(0) );
}

/**
 * @brief      Sets VX to the result of a bitwise and
 * 						 operation on a random number and NN
 */
void opcode::opCXNN()
{
	unsigned char x = (proc->getOP() & 0x0F00) >> 8;
	unsigned char v_nn = proc->getOP() & 0x00FF;

	
	// TODO: generate random byte in the following format
	int r = ((rand() % (0xF + 1 - 0x0)) + 0x0);
	proc->setV(x, r & v_nn);
	proc->incrementPC(1);
}

/**
 * @brief      			 Sprites stored in memory at location in index register (I),
 *						 8bits wide. Wraps around the screen. If when 
 *						 drawn, clears a pixel, register VF is set to 1 otherwise it is
 *						 zero. All drawing is XOR drawing (i.e. it toggles the screen pixels).
 *						 Sprites are drawn starting at position VX, VY. N is the number of 8bit 
 *						 rows that need to be drawn. If N is greater than 1,
 *						 second line continues at position VX, VY+1, and so on
 */
void opcode::opDXYN()
{
	unsigned char x = (proc->getOP() & 0x0F00) >> 8;
	unsigned char y = (proc->getOP() & 0x00F0) >> 4;

	// Wrap if going beyond screen boundaries
	int xPos = proc->getV(x) % c8_display::EM_WIDTH; 
	int yPos = proc->getV(y) % c8_display::EM_HEIGHT;

	proc->setV(0xF, 0);

	// Iterate over display
	for (int row = 0; row < c8_display::EM_HEIGHT; ++row)
	{
		uint8_t sprite = proc->mem.get(proc->getI() + row);

		for (int col = 0; col < 8; ++col)
		{
			int spritePixel = sprite & (0x80 >> col);
			int gfx_index = proc->gfx[(yPos + row) * c8_display::EM_WIDTH + (xPos + col)];

			if (spritePixel)
			{	
				// Check collision
				if (proc->gfx[gfx_index] == 0xFFFFFFFF)
					proc->setV(0xF, 1);
				
				proc->gfx[gfx_index] ^= 0xFFFFFFFF;
			}
		}
	}
	
	proc->drawFlag = true;
	proc->incrementPC(1);
}

/**
 * @brief      Skips the next instruction if the key stored in VX is pressed
 */
void opcode::opEX9E()
{
	proc->incrementPC(1);
}



/**
 * @brief      Skips the next instruction if the key stored in VX isn't pressed
 */
void opcode::opEXA1()
{
	proc->incrementPC(1);
}

/**
 * @brief      Sets VX to the value of the delay timer
 */
void opcode::opFX07()
{
	proc->incrementPC(1);
}

/**
 * @brief      A key press is awaited, and then stored in VX
 */
void opcode::opFX0A()
{
	proc->incrementPC(1);
}

/**
 * @brief      Sets the delay timer to VX
 */
void opcode::opFX15()
{
	proc->incrementPC(1);
}

/**
 * @brief      Sets the sound timer to VX
 */
void opcode::opFX18()
{
	proc->incrementPC(1);
}



/**
 * @brief      Adds VX to I
 */
void opcode::opFX1E()
{
	int x = (proc->getOP() & 0x0F00) >> 8;

	proc->setI(proc->getI() + x);

	proc->incrementPC(1);
}

/**
 * @brief      Sets I to the location of the sprite for the character in VX.
 *  					 Characters 0-F (in hexadecimal) are represented by a 4x5 font
 */
void opcode::opFX29()
{
	proc->incrementPC(1);
}

/**
 * @brief      Stores the Binary-coded decimal representation of VX,
 * 						 with the most significant of three digits at the address in I,
 * 						 the middle digit at I plus 1, and the least significant digit at
 * 						 I plus 2. (In other words, take the decimalrepresentation of VX,
 * 						 place the hundreds digit in memory at location in I,
 * 						 the tens digit at location I+1,
 * 						 and the ones digit at location I+2)
 */
void opcode::opFX33()
{
	proc->incrementPC(1);
}

/**
 * @brief      Stores V0 to VX in memory starting at address I
 */
void opcode::opFX55()
{
	int x = (proc->getOP() & 0x0F00) >> 8;

	for (int i = 0; i < x; i++)
		proc->mem.set( proc->getI() + i, proc->getV(x) );

	proc->incrementPC(1);
}

/**
 * @brief      Fills V0 to VX with values from memory starting at address I
 */
void opcode::opFX65()
{
	int x = (proc->getOP() & 0x0F00) >> 8;

	for (int i = 0; i < x; i++)
		proc->setV( i, proc->mem.get(proc->getI() + i) );

	proc->incrementPC(1);
}