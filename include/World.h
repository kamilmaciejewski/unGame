/*
 * world.h
 *
 *  Created on: 10 mar 2018
 *      Author: Kamil
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <SDL2/SDL.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "Creature.h"

class World {

    SDL_Surface* backgroundTexture = nullptr;
public:
    World();
    virtual ~World();
    void addCreature(Creature *);
    void updateAndDraw(long, SDL_Surface*);
    std::vector<Creature*> creatures;
};

#endif /* WORLD_H_ */
