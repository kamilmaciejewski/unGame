#ifndef UNGNEURONCONNECTION_H_
#define UNGNEURONCONNECTION_H_

#include <SDL2/SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "UNGGlobals.h"

class UNGNeuron; //forward declaration for cross-dependency

class UNGNeuronConnection {

friend class UNGNeuron;

public:

	UNGNeuronConnection(SDL_FPoint, UNGNeuron*);
	virtual ~UNGNeuronConnection();

private:
	uint32_t getColor();
	SDL_FPoint externalPos;
	UNGNeuron* neuron;
};

#endif /* UNGNEURONCONNECTION_H_ */
