#include <stdio.h>
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <boost/config/compiler/gcc.hpp>

#include "Zone.h"

Zone::Zone(int &x, int &y) {
	creatures = new std::vector<Creature*>();
	pos.x = x;
	pos.y = y;
}
void Zone::update(Creature *creature) {
	if (distance(pos, creature->pos) <= size) {
		if (std::find(creatures->begin(), creatures->end(), creature)
				== creatures->end()) {
			creatures->push_back(creature);
		}
	} else {
		auto index = std::find(creatures->begin(), creatures->end(), creature);
		if (index != creatures->end()) {
			creatures->erase(index);
		}
	}

}
void Zone::kickOut(Creature *creature) {
	auto index = std::find(creatures->begin(), creatures->end(), creature);
	if (index != creatures->end()) {
		creatures->erase(index);
	}
}
void Zone::draw(SDL_Renderer *renderer) {
	if (creatures->size() > 0) {
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, SDL_ALPHA_TRANSPARENT);
	} else {
		SDL_SetRenderDrawColor(renderer, 0x0, 0xFF, 0x0, SDL_ALPHA_TRANSPARENT);
	}
	SDL_RenderDrawPoint(renderer, pos.x, pos.y);
}

Zone::~Zone() {
	delete creatures;
}

