#ifndef __MEMORY_HPP__
#define __MEMORY_HPP__

/*
 *	Memory map
 *	0x000 - 0x1FF ( Chip 8 interpreter (contains font set in emu )
 *	0x050 - 0x0A0 ( Used for the build in font set )
 *	0x200 - 0xFFF ( Program ROM and work RAM )
 */

class memory
{
	public:
		memory();
		~memory();

		// Gets instruction at index
		unsigned char get(int);

	private:
		unsigned char mem[4096];

};

#endif