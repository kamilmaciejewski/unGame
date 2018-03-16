/*
 * world.cpp
 *
 *  Created on: 10 mar 2018
 *      Author: Kamil
 */

#include "World.h"

World::World() {
    srand(time(NULL));
    //TODO: ekammac, pass the screen size here.
    for (int i = 0; i < 99; i++) {
        Creature* creature = new Creature();
        creature->posX = rand() % 800;
        creature->posY = rand() % 800;
        addPlayer(creature);
    }

}

World::~World() {
    for (auto creature : creatures) {
            delete(&creature);
        }
}

void World::addPlayer(Creature* player) {
    creatures.push_back(*player);

}

void World::draw(SDL_Surface* surface) {
    for (auto &player : creatures) {
        player.draw(surface);
    }

}

