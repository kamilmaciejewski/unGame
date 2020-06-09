#include <iostream>
#include <stdio.h>
#include <UNGWorld.h>

World::World() {
	distribution = std::normal_distribution<double>(0.0, 0.3);
	logger = LoggingHandler::getLogger("WRLD");
	surface = SDL_LoadBMP("res/arrow.bmp");
	SDL_SetColorKey(surface, SDL_TRUE,
			SDL_MapRGB(surface->format, 0xff, 0x0, 0xff));
	SDL_SetSurfaceAlphaMod(surface, 100);
	if (surface == nullptr) {
		printf("Unable to load image: %s\n", SDL_GetError());
	}
	creaturesWorld.reserve(MAX_CREATURES);
	creaturesSdl.reserve(MAX_CREATURES);
	plants.reserve(MAX_PLANTS);

	settings = nullptr;
	initZones();
}

World::~World() {
	SDL_FreeSurface(surface);
	for (auto creature : creaturesWorld) {
		if (creature != nullptr) {
			creature = nullptr;
		}
	}
	creaturesWorld.clear();

//	for (auto creature : creaturesSdl) {
//		if (creature != nullptr) {
//			creature = nullptr;
//		}
//	}
//	creaturesSdl.clear();

	for (auto zone : zones) {
		if (zone != nullptr) {
			delete zone;
		}
	}
	zones.clear();

	for (auto plant : plants) {
		if (plant != nullptr) {
			delete plant;
		}
	}
	plants.clear();
}

void World::initZones() {

	for (unsigned int x = 0; x <= SIZE_W; x += SIZE_W / ZONE_RES) {
		for (unsigned int y = 0; y <= SIZE_H; y += SIZE_H / ZONE_RES) {
			zones.push_back(new Zone(x, y));
		}
	}

}

void World::addCreature(std::shared_ptr<Creature> creature) {
//	if (creaturesWorld.size() < MAX_CREATURES) {
//		creaturesWorld.push_back(creature);
//	} else {
//		logger->log(
//				"Slot not found WORLD" + std::to_string(creaturesWorld.size()));
//	}
//	if (settings->mode == Settings::GUI) {
//
//		if (creaturesSdl.size() < MAX_CREATURES) {
//			creaturesSdl.push_back(creature);
//		} else {
//			logger->log(
//					"Slot not found SDL" + std::to_string(creaturesSdl.size()));
//		}
//	}

//	creature = nullptr;
//	logger->setPermaLog("addCr", std::to_string(creature.use_count()));
}

std::shared_ptr<Creature> World::cloneAndRandomizeCreature(const std::shared_ptr<Creature> &creature){
	return std::make_shared<Creature>(*creature);
}

void World::addCreature(SDL_Point pos) {
	NeuralParams params(&generator, &distribution);
	std::shared_ptr<Creature> tmpCreature = std::make_shared<Creature>(surface,
			params);
	tmpCreature->setPos(SDL_FPoint { (float) pos.x, (float) pos.y });
	tmpCreature->rotate(0);
	tmpCreature->setInactive();
	addCreatureReuse(tmpCreature);
}

void World::addPlant(SDL_Point pos) {
	Plant *plant = new Plant();
	plant->setPos(SDL_FPoint { (float) pos.x, (float) pos.y });
	plant->setActive();
	plant->update();
	plants.push_back(plant);
	for (auto zone : zones) {
		zone->update(plant);
	}
}

void World::addCreatureReuse(std::shared_ptr<Creature> creature) {
	//TODO rewrite to use multiengine collected resource pool
	bool reuse = false;
	for (auto ptr = creaturesWorld.begin(); ptr < creaturesWorld.end(); ptr++) {
			if ((*ptr) == nullptr) {
				(*ptr) = creature;
				reuse = true;
				logger->log("CR world reuse");
				break;
			}
	}
	if(!reuse && creaturesWorld.size() < MAX_CREATURES){
		creaturesWorld.push_back(creature);
		logger->log("CR world add new");
	}

	if(settings->mode == Settings::GUI){
	reuse = false;
		for (auto ptr = creaturesSdl.begin(); ptr < creaturesSdl.end(); ptr++) {
				if ((*ptr) == nullptr) {
					(*ptr) = creature;
					reuse = true;
					logger->log("CR sdl reuse");
					break;
				}
		}
	if(!reuse && creaturesSdl.size() < MAX_CREATURES){
			creaturesSdl.push_back(creature);
			logger->log("CR sdl add new");
		}
	}

	creature = nullptr;
}
//TODO: Last two parameters should be a rectangle for zooming the screen.
void World::draw(SDL_Renderer *renderer) {

	int counter = 0;
	for (auto ptr = creaturesSdl.begin(); ptr < creaturesSdl.end(); ptr++) {
		if ((*ptr) != nullptr) {
			counter++;
			(*ptr)->draw(renderer, settings);
			if (!(*ptr)->isAlive()) {
				(*ptr) = nullptr;
				continue;
			}
		}
	}
	logger->setPermaLog("Size SDL:", std::to_string(counter));

	for (auto zone : zones) {
		zone->draw(renderer);
	}
	for (auto plant : plants) {
		plant->draw(renderer);
	}
//	for (auto creature : creatures) {
//		creature->draw(renderer, settings);
//		if (creature->isActive()) {
//			infoStr = creature->getInfo();
//	}
//	logger->setPermaLog("SDL size", std::to_string(creaturesSdl.size()));
//
//	for (ptr = creaturesSdl.begin(); ptr < creaturesSdl.end(); ptr++) {
//		if ((*ptr) != nullptr) {
//			(*ptr)->draw(renderer, settings);
//			if (!(*ptr)->isAlive()) {
//				(*ptr) = nullptr;
//				continue;
//			}
//		}
//	}
}

//	for (ptr = creaturesSdl.begin(); ptr < creaturesSdl.end(); ptr++) {
//		auto xxx = ptr;
//		std::shared_ptr<Creature> cr = *xxx;
//		if ((*ptr) != nullptr) {
//			auto xx = *ptr;
//			if (xx!=nullptr && !xx->isAlive()) {
//				(*ptr) = nullptr;
//				continue;
//			}
//			xx->draw(renderer, settings);
//		}
//	}
//		}
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

	int counter = 0;
	int maxGen = 0;
	double minEnergy = 255;
	for (auto ptr = creaturesWorld.begin(); ptr < creaturesWorld.end(); ptr++) {
		if ((*ptr) != nullptr) {
			counter++;
			if ((*ptr)->generations > maxGen) {
				maxGen = (*ptr)->generations;
			}
			(*ptr)->update(timeDelta, settings);
			if ((*ptr)->energy > 200){ //TODO this should be in creature, rewrite
				(*ptr)->energy = 100;
				addCreatureReuse(cloneAndRandomizeCreature(*ptr));

			}
			wrapPos(&(*ptr)->pos);
			for (auto zone : zones) {
				zone->update((*ptr));
				for (auto plant : *zone->plants) {
					SDL_Point tmpPos = { (int) (*ptr)->pos.x,
							(int) (*ptr)->pos.y };
					if (SDL_PointInRect(&tmpPos,
							&plant->getDrawable()->rect_draw)) {
						if ((*ptr)->energy < 255 && plant->energy > 0) {
							(*ptr)->energy += energryDelta * *timeDelta;
							plant->energy -= energryDelta * *timeDelta;
						}
					}
				}
			}

			if ((*ptr)->energy < minEnergy) {
				minEnergy = (*ptr)->energy;
			}
			if (!(*ptr)->isAlive()) {
				for (auto zone : zones) {
//					if (
					zone->kickOut(*ptr);
//							> 0) {
//						logger->log(
//								"Zone UC " + std::to_string(ptr->use_count()));
//					}
				}
				(*ptr) = nullptr;
				continue;
			}

		}
	}
	logger->setPermaLog("Size:", std::to_string(counter));
	logger->setPermaLog("Max Gen:", std::to_string(maxGen));

	for (auto plant : plants) {
		if (plant->energy < 255.0) {
			plant->energy += (energryDelta / ((plants.size() / 5)))
					* *timeDelta;
		}
	}
//	for (ptr = creaturesWorld.begin(); ptr < creaturesWorld.end(); ptr++) {
//		if (*ptr != nullptr) {
//			auto xx = *ptr;
//			if (xx!=nullptr && !xx->isAlive()) {
//				(*ptr) = nullptr;
//				continue;
//			}
//			xx->update(timeDelta, settings);
//				if (!(*ptr)->isAlive()) {
//					*ptr = nullptr;
//				}
//			for (auto zone : *zones) {
//				for (auto plant : *zone->plants) {
//					SDL_Point tmpPos = { (int) (*ptr)->pos.x,
//							(int) (*ptr)->pos.y };
//					if (SDL_PointInRect(&tmpPos,
//							&plant->getDrawable()->rect_draw)) {
//						if ((*ptr)->energy < 255 && plant->energy > 0) {
//							(*ptr)->energy += energryDelta * *timeDelta;
//							plant->energy -= energryDelta * *timeDelta;
//						};
//					}
//				}
//			}
//			wrapPos(&(*ptr)->pos);

//			if ((*ptr)->isActive()) {
//				logger->setPermaLog("active:", (*ptr)->getInfo());
//			}
//			}
//		}
}

void World::updateViewSense() {
	activeCreaturesCounter = 0;
	activePlantsCounter = 0;
	if (settings->look) {
		for (auto ptr = creaturesWorld.begin(); ptr < creaturesWorld.end();
				ptr++) {
			auto creature = *ptr;
			if (creature != nullptr) {
				if (creature->isAlive()) {
					++activeCreaturesCounter;
					creature->cleanupView();
					for (auto zone : zones) {
//					zone->update(creature);
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
//				} else {
//					for (auto zone : zones) {
//						zone->kickOut(creature);
//					}
//				if(creature!=nullptr){
//				logger->log("CR");
//				}
				}
			}
		}
		for (auto plant : plants) {
			if (!plant->isActive()) {
				for (auto zone : zones) {
					zone->kickOut(plant);
				}
			} else {
				++activePlantsCounter;
			}
		}
		logger->setPermaLog("active creatures:",
				std::to_string(activeCreaturesCounter));
	}
}

void World::updateNeuralNetworks() {
	for (auto ptr = creaturesWorld.begin(); ptr < creaturesWorld.end(); ptr++) {
		auto creature = *ptr;
		if (creature != nullptr) {
			if (creature->isAlive()) {
				creature->updateNeuralNet(settings);
			}
		}
	}
}

void World::setSettings(Settings *_settings) {
	settings = _settings;
}

void World::handleInput() {

	if (SDL_PointInRect(&settings->mousePos, &UNG_Globals::worldBox)
			&& settings->mark_active == true) {

		if (settings->btn_down_right == true) {
			if (settings->creature) {
				addCreature(settings->mousePos);
			} else {
				addPlant(settings->mousePos);
				settings->mark_active = false;
			}
		}

		if (settings->btn_down_left == true) {
			settings->mark_active = false;
			bool found = false;
			for (auto ptr = creaturesSdl.begin(); ptr < creaturesSdl.end();
					ptr++) {
				auto creature = *ptr;
				if (creature != nullptr) {

					if (!found
							&& SDL_PointInRect(&settings->mousePos,
									&creature->getDrawable()->rect_draw)) {
						creature->setActive();
						found = true;
					} else {
						creature->setInactive();
					}
				}
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
