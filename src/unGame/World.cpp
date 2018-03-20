/*
 * world.cpp
 *
 *  Created on: 10 mar 2018
 *      Author: Kamil
 */

#include <World.h>

World::World() {
    creatures = new std::vector<Creature*>();
    std::srand(time(nullptr));
    for (int i = 0; i < 99; i++) {
        addCreature(new Creature());
    }
}

World::~World() {
    SDL_FreeSurface(backgroundTexture);
    for (auto creature : *creatures) {
        if (creature != nullptr) {
            delete (creature);
        } else {
            std::cout << "Null, skip." << std::endl;
        }
    }
    creatures->clear();
    delete (&creatures);
}

void World::addCreature(Creature* creature) {

    creature->setPos(rand() % 800, rand() % 800);
    creature->rotate(rand() % 359);
    creature->setSpeed((0.3 + (rand() % 6) * 0.05));
    creature->setRotationSpeed(0.1 + (0.01 * (rand() % 20)));
//
//	creature->setPos(320,320);
//	creature->rotate(0);
//	creature->setSpeed(0.05);
//	creature->setRotationSpeed(0.03);

    creatures->push_back(creature);
}

void World::updateAndDraw(long timeDelta, SDL_Surface* surface) {
//    std::cout << "Time: " << timeDelta << std::endl;
    for (auto creature : *creatures) {
        creature->update(timeDelta);
        creature->draw(surface);
    }

}

