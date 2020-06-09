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
	float fov = 45;
	float speedFactor = 0.02;
	uint16_t viewDist = 200;
	uint16_t maxConnections = 10;
	uint16_t maxViewEntries = 100;
};

class Creature: public Object {

public:
	float energy = 255;
	std::vector<UNG_Vector*> *multiview;

	Creature(SDL_Surface*, NeuralParams);
	Creature(const Creature&);
	virtual ~Creature();

	void setRotationSpeed(float);
	void setSpeed(float);
	void setActive();
	void setInactive();

	void draw(SDL_Renderer*, Settings*);
	void update(const uint32_t*, Settings*);
	void updateNeuralNet(Settings*);
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
	void mapNeuralNetworkOutput();

private:
	Genotype genotype;
	const uint8_t ROTATION_STEP = 3;
	float metabolism_factor = 0.05;

	UNG_Vector* lookAt(const SDL_FPoint point);
	UNGNeuralNetwork *neuralNet;
	bool activeState = false;
	float speed = 0, rotation_speed = 0;
//	UNGLogger* logger;
};

#endif /* CREATURE_H_ */
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
	namespace feno {
	float fov = 45;
	float speedFactor = 0.01;
	uint16_t viewDist = 100;
	}
	namespace neural {
	uint maxConnections = 10;
	}
};

class Creature: public Object {
	Genotype genotype;

//	const float FOV = 45.0;
	const uint8_t ROTATION_STEP = 3;
	const uint16_t MAX_VIEW_ENTRIES = 100;
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
	void updateNeuralNet(Settings*);
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
	void mapNeuralNetworkOutput();

private:
	UNG_Vector* lookAt(const SDL_FPoint point);
	UNGNeuralNetwork neuralNet;
	bool activeState = false;
	float speed = 0, rotation_speed = 0;
	std::string tmp = "";
};

#endif /* CREATURE_H_ */
