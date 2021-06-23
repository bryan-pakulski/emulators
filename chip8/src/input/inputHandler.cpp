#include "inputHandler.hpp"
#include <algorithm>

inputHandler::inputHandler() {
	
}

/**
 * Processes an SDL event and checks the set up key mappings, processor memory is then updated to allow for opcodes to correctly recognise the input
 *
 * @param e SDL event
 * @param proc CPU pointer
 */
void inputHandler::processInput(SDL_Event e, cpu* proc) {
	if (e.type == SDL_KEYDOWN) {
		int index = -1;
		auto search = keyMap.find(e.key.keysym.sym);

		if ( search != keyMap.end() ) {
			index = search->second;
		}

		if (index != -1) {
			proc->setKey(index, 0x1);
		}
	} else if (e.type == SDL_KEYUP) {
		int index = -1;
		auto search = keyMap.find(e.key.keysym.sym);

		if ( search != keyMap.end() ) {
			index = search->second;
		}

		if (index != -1) {
			proc->setKey(index, 0x0);
		}
	}
	

}