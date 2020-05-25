#ifndef CREATURE_H_
#define CREATURE_H_

#include <boost/config/compiler/gcc.hpp>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <cmath>

#include "SDL2_rotozoom.h"
#include "UNGNeuralNetwork.h"
#include "UNGGlobals.h"
#include "UNGObject.h"
#include "UNGPlant.h"
#include "UNGLoggingHandler.h"


class Creature: public Object {

	const float FOV = 45.0;
	const uint8_t VIEW_DIST = 100;
	const uint8_t ROTATION_STEP = 3;
	const uint16_t MAX_VIEW_ENTRIES = 100;
	UNGLogger *logger;
	float metabolism_factor = 0.01;

public:
	float energy = 255;
	std::vector<UNG_Vector*> *multiview;

	Creature(SDL_Surface*);
	virtual ~Creature();

	void setRotationSpeed(float&);
	void setSpeed(float&);
	void setActive();
	void setInactive();

	void draw(SDL_Renderer*, Settings*);
	void update(const uint32_t*, Settings*);
	void updateNeuralNet();
	void wrapScreenPos();
	void move(const uint32_t*);
	void rotate(const float&);

	bool isActive();
	bool isAlive();
	void cleanupView();
	std::string getInfo();
	bool lookAt(const Creature*);
	bool lookAt(const Plant*);
	void mapViewOnNeuralNetwork(UNG_Vector*);

private:
	UNG_Vector* lookAt(const SDL_FPoint point);
	UNGNeuralNetwork neuralNet;
	bool activeState = false;
	float speed = 0, rotation_speed = 0;
};

#endif /* CREATURE_H_ */
