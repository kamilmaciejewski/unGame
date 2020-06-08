#ifndef WORLD_H_
#define WORLD_H_

#include <SDL2/SDL.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <thread>

#include "UNGCreature.h"
#include "UNGGlobals.h"
#include "UNGLoggingHandler.h"
#include "UNGPlant.h"
#include "UNGZone.h"

class World {
	const unsigned int ZONE_RES = 10;
	const unsigned int SIZE_W = 985; //TODO: Size should be independent from the screen
	const unsigned int SIZE_H = 770; //TODO: Size should be independent from the screen
	const unsigned int MAX_CREATURES = 100000;
	const unsigned int MAX_PLANTS = 100000;
	uint32_t activeCreaturesCounter = 0;
	uint32_t activePlantsCounter = 0;
	float energryDelta = 0.01;

//	SDL_Surface *backgroundTexture = nullptr;

	Settings *settings;
	std::vector<std::shared_ptr<Creature>> creaturesWorld;
	std::vector<std::shared_ptr<Creature>> creaturesSdl;
	std::vector<Plant*> plants;
	std::vector<Zone*> zones;

	void wrapPos(SDL_FPoint*);
	UNGLogger *logger;

public:

	std::default_random_engine generator;
	std::normal_distribution<double> distribution;
	World();
	virtual ~World();
	SDL_Surface *surface;

	void handleInput();
	void draw(SDL_Renderer*);
	void addCreature(SDL_Point);
	void addCreature(std::shared_ptr<Creature>);
	void addPlant(SDL_Point);
	void addCreatureReuse(std::shared_ptr<Creature>);
	void initZones();
	void update(uint32_t*);
	void updateViewSense();
	void updateNeuralNetworks();
	void setSettings(Settings*);
};

#endif /* WORLD_H_ */
