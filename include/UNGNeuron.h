#ifndef UNGNEURON_H_
#define UNGNEURON_H_

#include <SDL2/SDL.h>
#include <string>
#include <SDL2_gfxPrimitives.h>
#include <vector>
#include "UNGGlobals.h"
#include "UNGNeuronConnection.h"
#include "UNGVector.h"

class UNGNeuron {
public:
	SDL_FPoint pos;
	UNG_Vector vect = UNG_Vector { &pos };
	double treshhold = 0.1;
	std::string id;
	std::vector<std::pair<double, UNGNeuronConnection*>> *connections;
//	const uint32_t maxConnections = 100;
	bool state = false;

	UNGNeuron(SDL_FPoint, std::string, float);
	virtual ~UNGNeuron();

	void calculate();
	void draw(SDL_Renderer*);
	uint32_t getColor();

private:
};
#endif /* UNGNEURON_H_ */
