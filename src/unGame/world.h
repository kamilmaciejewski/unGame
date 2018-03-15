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
#include "player.h"

class World {

    SDL_Surface* backgroundTexture = NULL;
public:
    World();
    virtual ~World();
    void addPlayer(Player player);
    void draw(SDL_Surface*);
    std::vector<Player> players;
};

#endif /* WORLD_H_ */
