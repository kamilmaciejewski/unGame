/*
 * world.cpp
 *
 *  Created on: 10 mar 2018
 *      Author: Kamil
 */

#include "World.h"

World::World() {
    Player player0;
    addPlayer(player0);

}

World::~World() {
    // TODO Auto-generated destructor stub
}

void World::addPlayer(Player player) {
    players.push_back(player);

}

void World::draw(SDL_Surface* surface){
    for (auto &player : players){
        player.draw(surface);
        }

}

