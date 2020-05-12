#ifndef WORLD_H_
#define WORLD_H_

#include <SDL2/SDL.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "Creature.h"
#include "Plant.h"
#include "Zone.h"
#include "Globals.h"
#include "UNGLoggingHandler.h"

class World {
	const unsigned int ZONE_RES = 10;
	const unsigned int SIZE_W = 1000;
	const unsigned int SIZE_H = 1000;
	const unsigned int MAX_CREATURES = 100000;
	const unsigned int MAX_PLANTS = 100000;

//	SDL_Surface *backgroundTexture = nullptr;

	Settings *settings;
	std::vector<Creature*> *creatures;
	std::vector<Plant*> *plants;
	std::vector<Zone*> *zones;
	std::vector<Creature*>::iterator ptr;

	void wrapPos(SDL_FPoint*);
	UNGLogger* logger;

public:

	World();
	virtual ~World();
	SDL_Surface *surface;

	void markActiveObjectByMousePos(SDL_Point);
	void draw(SDL_Renderer*);
	void addCreature(Creature*);
	void addCreatureReuse(Creature*);
	void initZones();
	void update(uint32_t*);
	void updateViewSense();
	void setSettings(Settings*);
};

#endif /* WORLD_H_ */
