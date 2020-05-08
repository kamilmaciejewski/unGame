#include <World.h>
#include <iostream>
#include <stdio.h>

World::World() {
//	std::srand(time(nullptr)); ??? Is this needed?
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

	settings = nullptr;
	initZones();
}

World::~World() {
//	SDL_FreeSurface(backgroundTexture);  //Probably not used
	SDL_FreeSurface(surface);
	for (auto creature : *creatures) {
		if (creature != nullptr) {
			delete (creature);
		}
	}
	creatures->clear();
	delete creatures;

	for (auto zone : *zones) {
		if (zone != nullptr) {
			delete zone;
		}
	}
	zones->clear();
	delete zones;
}

void World::initZones() {

	for (int x = 0; x <= SIZE_W; x += SIZE_W / zoneRes) {
		for (int y = 0; y <= SIZE_H; y += SIZE_H / zoneRes) {
			zones->push_back(new Zone(x, y));
		}
	}

}

void World::addCreature(Creature *creature) {
	creatures->push_back(creature);
	log("Add new" + std::to_string(creatures->size()));
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
			creature->setPos(creature_->pos);
			creature->rotate(creature_->getDrawable()->rot_angle);
			//creature->setSpeed();
			//creature->setRotationSpeed(speedZero);
//			creature->setAlpha(255);
			creature->setInactive();
			creature->energy = 255;
			delete creature_;
			log("Add creature reuse: " + std::to_string(creatures->size()));
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
	for (auto zone : *zones) {
		zone->draw(renderer);
	}
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
		wrapPos(&creature->pos);

		if (creature->isActive()) {
			infoStr = creature->getInfo();
		}
	}
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
		bool found = false;
		for (auto creature : *creatures) {
			if (!found
					&& SDL_PointInRect(&mousePos,
							&creature->getDrawable()->rect_draw)) {
				creature->setActive();
				found = true;
			} else {
				creature->setInactive();
			}
		}
	}

}

void World::log(std::string message) {
	if (logger != nullptr) {
		logger->push(message);
	}
}

void World::wrapPos(SDL_FPoint *pos) {
	if (pos->x < 0) {
		pos->x = SIZE_W + pos->x;
	} else if (pos->x > SIZE_W) {
		pos->x = pos->x - SIZE_W;
	}
	if (pos->y < 0) {
		pos->y = SIZE_H + pos->y;
	} else if (pos->y > SIZE_H) {
		pos->y = pos->y - SIZE_H;
	}
}
