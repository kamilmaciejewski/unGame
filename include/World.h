#ifndef WORLD_H_
#define WORLD_H_

#include <SDL2/SDL.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "Creature.h"
#include "Zone.h"

class World {
	int zoneRes = 10;
	SDL_Surface *backgroundTexture = nullptr;
	Settings *settings;
	std::vector<Creature*> *creatures;
	std::vector<Zone*> *zones;
public:

	std::string infoStr;
	void markActiveObjectByMousePos(SDL_Point);
	void draw(SDL_Renderer*);
	World();
	virtual ~World();
	void addCreature(Creature*);
	void initZones();
	void update(uint32_t*);
	void updateViewSense();
	void setSettings(Settings*);
	SDL_Surface *surface;
};

#endif /* WORLD_H_ */
