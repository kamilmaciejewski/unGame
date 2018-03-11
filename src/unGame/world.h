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

class world {

    SDL_Surface backgroundTexture;
public:
    world();
    virtual ~world();
    void addPlayer(player player);
    void draw(SDL_Surface surface);
    std::vector<player> players;
};

#endif /* WORLD_H_ */
