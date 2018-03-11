/*
 * world.cpp
 *
 *  Created on: 10 mar 2018
 *      Author: Kamil
 */

#include "world.h"

world::world() {
    // TODO Auto-generated constructor stub

}

world::~world() {
    // TODO Auto-generated destructor stub
}

void world::addPlayer(player pplayer){
    players.push_back(pplayer);
}

