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
	float baseEnergryDelta = 0.0008;
	float energryDelta = baseEnergryDelta;
	float baseScreenWrapPenality = 10.0;
	float screenWrapPenality = baseScreenWrapPenality;

//	SDL_Surface *backgroundTexture = nullptr;

	Settings *settings;
	std::vector<std::shared_ptr<Creature>> creaturesSdl{};
	std::vector<Plant*> plants{};
	std::vector<Zone*> zones{};

	bool wrapPos(SDL_FPoint*);
	UNGLogger *logger;

	//world stats
	uint64_t count = 0;
	uint64_t maxCount = 0;
	uint64_t maxGen = 0;
	uint64_t maxGenEver = 0;
	uint64_t maxCountAtMaxGenEver = 0;
	float maxScreenWrapPenalityAtMaxGenEver = 0.0;
	float minEneryDeltaAtMaxGenEver = 0.0;
	uint64_t clonesCounter = 0;
	uint64_t nextId = 100;

public:

	std::vector<std::shared_ptr<Creature>> creaturesWorld{}; //private
	std::default_random_engine generator;
	std::normal_distribution<double> distribution;
	World();
	virtual ~World();
	SDL_Surface *surface;

	void handleInput();
	void draw(SDL_Renderer*);
	void addCreature(SDL_Point);
	std::shared_ptr<Creature> cloneAndRandomizeCreature(const std::shared_ptr<Creature> &);
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
