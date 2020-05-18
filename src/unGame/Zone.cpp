#include <UNGZone.h>

Zone::Zone(unsigned int &x, unsigned int &y) {
	creatures = new std::vector<Creature*>();
	plants = new std::vector<Plant*>();
	pos.x = x;
	pos.y = y;
}
void Zone::update(Creature* creature) {
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
void Zone::update(Plant *plant) {
	if (distance(pos, plant->pos) <= size) {
		if (std::find(plants->begin(), plants->end(), plant) == plants->end()) {
			plants->push_back(plant);
		}
	}
}

void Zone::kickOut(Creature *creature) {
	auto index = std::find(creatures->begin(), creatures->end(), creature);
	if (index != creatures->end()) {
		creatures->erase(index);
	}
}
void Zone::kickOut(Plant *plant) {
	auto index = std::find(plants->begin(), plants->end(), plant);
	if (index != plants->end()) {
		plants->erase(index);
	}
}

void Zone::draw(SDL_Renderer *renderer) {
	if (creatures->size() > 0 || plants->size() > 0) {
		SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, SDL_ALPHA_TRANSPARENT);
	} else {
		SDL_SetRenderDrawColor(renderer, 0x0, 0xFF, 0x0, SDL_ALPHA_TRANSPARENT);
	}
	SDL_RenderDrawPoint(renderer, pos.x, pos.y);
}

Zone::~Zone() {
	creatures->clear();
	delete creatures;
}

