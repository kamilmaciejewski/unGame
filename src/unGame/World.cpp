#include <World.h>
#include <iostream>
#include <stdio.h>

World::World() {
	surface = SDL_LoadBMP("res/arrow.bmp");
	SDL_SetColorKey(surface, SDL_TRUE,
			SDL_MapRGB(surface->format, 0xff, 0x0, 0xff));
	SDL_SetSurfaceAlphaMod(surface, 100);
	if (surface == nullptr) {
		printf("Unable to load image: %s\n", SDL_GetError());
	}
	creatures = new std::vector<Creature*>();
	creatures->reserve(maxCreatures);
	zones = new std::vector<Zone*>();

	std::srand(time(nullptr));
	settings = nullptr;
	initZones();
}

World::~World() {
	SDL_FreeSurface(backgroundTexture);
	SDL_FreeSurface(surface);
	for (auto creature : *creatures) {
		if (creature != nullptr) {
			delete (creature);
		}
	}
	creatures->clear();
	delete (creatures);

	for (auto zone : *zones) {
		if (zone != nullptr) {
			delete (zone);
		}
	}
	zones->clear();
	delete (zones);
}

void World::initZones() {

	for (int x = 0; x <= UNG_Globals::SCREEN_W;
			x += UNG_Globals::SCREEN_W / zoneRes) {
		for (int y = 0; y <= UNG_Globals::SCREEN_H;
				y += UNG_Globals::SCREEN_H / zoneRes) {
			zones->push_back(new Zone(x, y));
		}
	}

}
void World::addCreature(Creature *creature) {
	infoStr = "Add new" + std::to_string(creatures->size());
	creatures->push_back(creature);
}

void World::addCreatureReuse(Creature *creature_) {

//	for (ptr = creatures->begin(); ptr < creatures->end(); ptr++) {
//		if (!(*ptr)->isAlive()) {
//
//			reused = true;
//		}
//	}

	for (auto creature : *creatures) {
		if (!creature->isAlive()) {
			infoStr = "Reuse" + std::to_string(creatures->size());
			creature->setPos(creature_->pos);
//			creature->rotate(creature_->getDrawable()->rot_angle);
			//creature->setSpeed();
			//creature->setRotationSpeed(speedZero);
//			creature->setAlpha(255);
			creature->setInactive();
			creature->energy = 255;
			delete creature_;
			return;
		}
	}
	if (creatures->size() < maxCreatures) {
		addCreature(creature_);
	} else {
		infoStr = "Slot not found" + std::to_string(creatures->size());
	}
}
//TODO: Last two parameters should be a rectangle for zooming the screen.
void World::draw(SDL_Renderer *renderer) {

	//vector cleanup
	//	*creatures->erase(std::remove(begin(*creatures), end(*creatures), nullptr),
	//			end(*creatures));

	for (auto creature : *creatures) {
		creature->draw(renderer, settings);
//		if (creature->isActive()) {
//			infoStr = creature->getInfo();
//		}
	}
//	for (auto zone : *zones) {
//		zone->draw(renderer);
//	}
}
//remove ptr to dead
//for (ptr = creatures->begin(); ptr < creatures->end(); ptr++) {
//		if (*ptr != nullptr) {
//			if (!(*ptr)->isAlive()) {
//				for (auto zone : *zones) {
//					zone->kickOut(*ptr);
//				}
//				*ptr = nullptr;
//			}
//		}
//	}
void World::update(uint32_t *timeDelta) {
	for (auto creature : *creatures) {
		creature->update(timeDelta, settings);
		if (creature->isActive()) {
			infoStr = creature->getInfo();
		}
	}
//	infoStr = "size: " + std::to_string(creatures->size());
}

void World::updateViewSense() {
	if (settings->look) {
		for (auto creature : *creatures) {
			if (creature->isAlive()) {
				creature->cleanupView();
				for (auto zone : *zones) {
					zone->update(creature);
					if (distance(creature->pos, zone->pos) <= zone->size) {
//					for (auto otherCreature : * creatures){
						for (auto otherCreature : *zone->creatures) {
//						if (
							if (otherCreature != nullptr) {
								creature->lookAt(otherCreature);
							}
//								) {
//							break;
						}
					}
				}
			} else {
				for (auto zone : *zones) {
					zone->kickOut(creature);
				}
			}
		}
	}
}

void World::setSettings(Settings *_settings) {
	settings = _settings;
}

void World::markActiveObjectByMousePos(SDL_Point mousePos) {

	if (settings->btn_down_right == true) {
		float speed = 0.05;
		Creature *tmpCreature = new Creature(surface);
		tmpCreature->setPos(
				SDL_FPoint { (float) mousePos.x, (float) mousePos.y });
		tmpCreature->rotate(0);
		tmpCreature->setSpeed(speed);
		tmpCreature->setRotationSpeed(speed);
		tmpCreature->setInactive();
		addCreatureReuse(tmpCreature);
	}

	if (settings->mark_active == true) {
		settings->mark_active = false;
		for (auto creature : *creatures) {
			if (SDL_PointInRect(&mousePos,
					&creature->getDrawable()->rect_draw)) {
				creature->setActive();
				return;
			} else {
				creature->setInactive();
			}
		}
	}

}

