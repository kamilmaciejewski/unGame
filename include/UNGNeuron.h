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
	bool isActive = false;
	SDL_FPoint pos;
	SDL_FPoint posDirection;

	SDL_Rect rectPos;
	UNG_Vector vect = UNG_Vector { &pos };
	std::string id;
	std::vector<std::pair<float, UNGNeuronConnection*>> *connections;
	bool state = false;

	UNGNeuron(SDL_FPoint, std::string, float, uint16_t, float, float, float);
	virtual ~UNGNeuron();

	void calculateValue();
	void calculateNet();
	void resetNet();
	void calculate();
	void draw(SDL_Renderer*);
	uint32_t getColor();
	uint16_t fov;
	float connWeightAngleFactor;
	float treshhold;
	float net = 0, sigm = 0; //TODO: Private

private:
	float tresholdDelta=0.000001;
};
#endif /* UNGNEURON_H_ */

