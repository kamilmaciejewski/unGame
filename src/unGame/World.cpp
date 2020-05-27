#include <iostream>
#include <stdio.h>
#include <UNGWorld.h>

World::World() {
	logger = LoggingHandler::getLogger("WRLD");
	surface = SDL_LoadBMP("res/arrow.bmp");
	SDL_SetColorKey(surface, SDL_TRUE,
			SDL_MapRGB(surface->format, 0xff, 0x0, 0xff));
	SDL_SetSurfaceAlphaMod(surface, 100);
	if (surface == nullptr) {
		printf("Unable to load image: %s\n", SDL_GetError());
	}
	creatures = new std::vector<Creature*>();
	creatures->reserve(MAX_CREATURES);
	plants = new std::vector<Plant*>();
	plants->reserve(MAX_PLANTS);
	zones = new std::vector<Zone*>();

	settings = nullptr;
	initZones();
}

World::~World() {
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
	for (auto plant : *plants) {
			if (plant != nullptr) {
				delete plant;
			}
		}
	plants->clear();
	delete plants;
	delete logger;
}

void World::initZones() {

	for (unsigned int x = 0; x <= SIZE_W; x += SIZE_W / ZONE_RES) {
		for (unsigned int y = 0; y <= SIZE_H; y += SIZE_H / ZONE_RES) {
			zones->push_back(new Zone(x, y));
		}
	}

}

void World::addCreature(Creature *creature) {
	creatures->push_back(creature);
}

void World::addCreature(SDL_Point pos){
			float speed = 0.05;
			Creature *tmpCreature = new Creature(surface);
			tmpCreature->setPos(
					SDL_FPoint { (float) pos.x, (float) pos.y });
			tmpCreature->rotate(0);
			tmpCreature->setSpeed(speed);
			tmpCreature->setRotationSpeed(speed);
			tmpCreature->setInactive();
			addCreatureReuse(tmpCreature);
}

void World::addPlant(SDL_Point pos) {
	Plant *plant = new Plant();
	plant->setPos(SDL_FPoint { (float) pos.x, (float) pos.y });
	plant->setActive();
	plant->update();
	plants->push_back(plant);
	for (auto zone : *zones) {
		zone->update(plant);
	}
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
			return;
		}
	}
	if (creatures->size() < MAX_CREATURES) {
		addCreature(creature_);
	} else {
		logger->log("Slot not found" + std::to_string(creatures->size()));
	}
}
//TODO: Last two parameters should be a rectangle for zooming the screen.
void World::draw(SDL_Renderer *renderer) {

	//vector cleanup
	//	*creatures->erase(std::remove(begin(*creatures), end(*creatures), nullptr),
	//			end(*creatures));

	for (auto zone : *zones) {
		zone->draw(renderer);
	}
	for (auto plant : *plants) {
		plant->draw(renderer);
	}
	for (auto creature : *creatures) {
		creature->draw(renderer, settings);
//		if (creature->isActive()) {
//			infoStr = creature->getInfo();
//		}
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
			logger->setPermaLog("active:", creature->getInfo());
		}
		logger->setPermaLog("Size", std::to_string(creatures->size()));
	}
}

void World::updateViewSense() {
	activeCreaturesCounter = 0;
	activePlantsCounter = 0;
	if (settings->look) {
		for (auto creature : *creatures) {
			if (creature->isAlive()) {
				++activeCreaturesCounter;
				creature->cleanupView();
				for (auto zone : *zones) {
					zone->update(creature);
					for (auto plant : *zone->plants) {
						if (plant != nullptr) {
							creature->lookAt(plant);
						}
//					if (distance(creature->pos, zone->pos) <= zone->size) {
//						for (auto otherCreature : *zone->creatures) {
//							if (otherCreature != nullptr) {
//								creature->lookAt(otherCreature);
//							}

//						}
					}
				}
			} else {
				for (auto zone : *zones) {
					zone->kickOut(creature);
				}
			}
		}
	}
	for (auto plant : *plants) {
		if (!plant->isActive()) {
			for (auto zone : *zones) {
				zone->kickOut(plant);
			}
		} else {
			++activePlantsCounter;
		}
	}
	logger->setPermaLog("active creatures:", std::to_string(activeCreaturesCounter));
	logger->setPermaLog("active plants:", std::to_string(activePlantsCounter));
}

void World::updateNeuralNetworks(){
	for (auto creature : *creatures) {
		creature->updateNeuralNet();
	}

}

void World::setSettings(Settings *_settings) {
	settings = _settings;
}

void World::handleInput(SDL_Point mousePos) {

	if (settings->btn_down_right == true) {
		if (settings->creature) {
			addCreature(mousePos);
		} else {

			addPlant(mousePos);
		}
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
