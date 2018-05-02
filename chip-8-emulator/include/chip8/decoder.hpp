// handles loading games and parsing instructions
// to send into memory for the cpu

#ifndef __DECODER_HPP__
#define __DECODER_HPP__

#include <iostream>
#include <string>

class decoder
{
	public:
		decoder(std::string);
		~decoder();

	private:
		std::string path;
};

#endif