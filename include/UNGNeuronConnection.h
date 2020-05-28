#ifndef UNGNEURONCONNECTION_H_
#define UNGNEURONCONNECTION_H_

#include <SDL2/SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "UNGGlobals.h"
#include <string>

class UNGNeuron; //forward declaration for cross-dependency

class UNGNeuronConnection {

friend class UNGNeuron;

public:

	UNGNeuronConnection(SDL_FPoint, UNGNeuron*, std::string);
	virtual ~UNGNeuronConnection();

private:
	std::string id;
	uint32_t getColor();
	SDL_FPoint externalPos;
	UNGNeuron* neuron;
};

#endif /* UNGNEURONCONNECTION_H_ */
