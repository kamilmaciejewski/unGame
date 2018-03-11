/*
 * world.cpp
 *
 *  Created on: 10 mar 2018
 *      Author: Kamil
 */

#include "World.h"

World::World() {
    // TODO Auto-generated constructor stub

}

World::~World() {
    // TODO Auto-generated destructor stub
}

void World::addPlayer(Player player) {
    players.push_back(player);
}

