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
        creature->setPos(rand() % 800,rand() % 800);
        creature->setRotationAngle(rand() % 359);
        creature->setSpeed(5+ rand() % 10);
        creature->setRotationSpeed((rand() % 40)-20);

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

