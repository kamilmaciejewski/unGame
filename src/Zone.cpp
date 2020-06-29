#include <UNGZone.h>
#include "SDL2_gfxPrimitives.h" //tmp

Zone::Zone(unsigned int &x, unsigned int &y) {
	creatures = new std::vector<std::shared_ptr<Creature>>();
	plants = new std::vector<Plant*>();
	pos.x = x;
	pos.y = y;
}
void Zone::update(std::shared_ptr<Creature> creature) {
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
	else {
		kickOut(plant);
	}
}

long Zone::kickOut(std::shared_ptr<Creature> creature) {
	auto index = std::find(creatures->begin(), creatures->end(), creature);
	if (index != creatures->end()) {
		creatures->erase(index);
		return creature.use_count();
	}
	return 0;
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
		stringColor(renderer, pos.x, pos.y + 10,
				("p:" + std::to_string(plants->size()) + "c:"
						+ std::to_string(creatures->size())).c_str(),
				UNG_Globals::GREEN);
	} else {
		SDL_SetRenderDrawColor(renderer, 0x0, 0xFF, 0x0, SDL_ALPHA_TRANSPARENT);
	}
	SDL_RenderDrawPoint(renderer, pos.x, pos.y);
}

Zone::~Zone() {
	creatures->clear();
	delete creatures;
	plants->clear();
	delete plants;
}

