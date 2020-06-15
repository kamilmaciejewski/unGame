#ifndef CREATURE_H_
#define CREATURE_H_

#include <boost/config/compiler/gcc.hpp>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <cmath>

#include "SDL2_rotozoom.h"
#include <SDL2_gfxPrimitives.h>
#include "UNGNeuralNetwork.h"
#include "UNGGlobals.h"
#include "UNGObject.h"
#include "UNGPlant.h"

struct Genotype {

	uint16_t maxViewEntries = 100;
};

class Creature: public Object {

public:
	float energy = 199;
	uint16_t generations = 0;
	std::vector<UNG_Vector*> *multiview;
	int id=0, parentId=0, ancessorId=0;


	Creature(SDL_Surface*, NeuralParams, int);
//	Creature(SDL_Surface*, NeuralParams);
	Creature(const Creature&, int);
//	Creature(const Creature&);
	virtual ~Creature();

	void setRotationSpeed(float);
	void setSpeed(float);
	void setActive();
	void setInactive();

	void draw(SDL_Renderer*, Settings*);
	void update(const uint32_t*, Settings*);
	void updateNeuralNet(Settings*);
	void wrapScreenPos();
	void move(const uint32_t&);
	void rotate(const float&);

	bool isActive();
	bool isAlive();
	void cleanupView();
	std::string getInfo();
	bool lookAt(const Creature*);
	bool lookAt(const Plant*);
	void mapViewOnNeuralNetwork(UNG_Vector*);
	void mapNeuralNetworkOutput();
	float feed_factor = 1.0;

private:
	float tmpSpeed = 0;
	Genotype genotype;
	const uint8_t ROTATION_STEP = 3;
	float metabolism_factor = 0.045;
	float neural_factor = 0.015;

	UNG_Vector* lookAt(const SDL_FPoint point);
	UNGNeuralNetwork *neuralNet;
	bool activeState = false;
	float rotation_speed = 0;
};

#endif /* CREATURE_H_ */
