#include <iostream>
#include <stdio.h>
#include <UNGWorld.h>
using namespace std;

World::World() {
	distribution = normal_distribution<double>(0.0, 0.3);
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

void World::addCreature(shared_ptr<Creature> creature) {
//	if (creaturesWorld.size() < MAX_CREATURES) {
//		creaturesWorld.push_back(creature);
//	} else {
//		logger->log(
//				"Slot not found WORLD" + to_string(creaturesWorld.size()));
//	}
//	if (settings->mode == Settings::GUI) {
//
//		if (creaturesSdl.size() < MAX_CREATURES) {
//			creaturesSdl.push_back(creature);
//		} else {
//			logger->log(
//					"Slot not found SDL" + to_string(creaturesSdl.size()));
//		}
//	}

//	creature = nullptr;
//	logger->setPermaLog("addCr", to_string(creature.use_count()));
}

shared_ptr<Creature> World::cloneAndRandomizeCreature(
		const shared_ptr<Creature> &creature) {
	logger->log(
			"Cl gen:" + to_string(creature->generations) + " -> "
					+ to_string(creature->id) + "("
					+ to_string(creature->parentId) + ";"
					+ to_string(creature->ancessorId) + ") to: "
					+ to_string(nextId + 1)); //TODO: getter to gen info string
	return make_shared<Creature>(*creature, nextId++);
}

void World::addCreature(SDL_Point pos) {
	NeuralParams params(&generator, &distribution);
	for (int i = 0; i < 10; i++) {
		params.randomize();
	}
	shared_ptr<Creature> tmpCreature = make_shared<Creature>(surface,
			params, nextId++);
	tmpCreature->setPos(SDL_FPoint { (float) pos.x, (float) pos.y });
	tmpCreature->rotate(rand() % 359);
	tmpCreature->setInactive();
	addCreatureReuse(tmpCreature);
}

void World::addPlant(SDL_Point pos) {
	Plant *plant = new Plant(SDL_FPoint { (float) pos.x, (float) pos.y });
	plants.push_back(plant);
	for (auto zone : zones) {
		zone->update(plant);
	}
}

void World::addCreatureReuse(shared_ptr<Creature> creature) {
	//TODO rewrite to use multiengine collected resource pool
	bool reuse = false;
	for (auto ptr = creaturesWorld.begin(); ptr < creaturesWorld.end(); ptr++) {
		if ((*ptr) == nullptr) {
			(*ptr) = creature;
			reuse = true;
			break;
		}
	}
	if (!reuse && creaturesWorld.size() < MAX_CREATURES) {
		creaturesWorld.push_back(creature);
	}

	if (settings->mode == Settings::GUI) {
		reuse = false;
		for (auto ptr = creaturesSdl.begin(); ptr < creaturesSdl.end(); ptr++) {
			if ((*ptr) == nullptr) {
				(*ptr) = creature;
				reuse = true;
				break;
			}
		}
		if (!reuse && creaturesSdl.size() < MAX_CREATURES) {
			creaturesSdl.push_back(creature);
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
//	logger->setPermaLog("Size SDL", to_string(counter));

	if (settings->draw_vectors) {
		for (auto zone : zones) {
			zone->draw(renderer);
		}

	}
		for (auto plant : plants) {
			if (plant->isAlive() && settings->draw_textures) {
				plant->draw(renderer);
			}
		}

//	for (auto creature : creatures) {
//		creature->draw(renderer, settings);
//		if (creature->isActive()) {
//			infoStr = creature->getInfo();
//	}
//	logger->setPermaLog("SDL size", to_string(creaturesSdl.size()));
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
//		shared_ptr<Creature> cr = *xxx;
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
	maxGen = 0;
	count = 0;

	for (auto ptr = creaturesWorld.begin(); ptr < creaturesWorld.end(); ptr++) {
		if ((*ptr) != nullptr) {
			count++;
			if ((*ptr)->generations > maxGen) {
				maxGen = (*ptr)->generations;
			}
			if (settings->rotate) {
				(*ptr)->update(timeDelta, settings);
				if ((*ptr)->energy > 200) { //TODO this should be in creature, rewrite
					(*ptr)->energy = 100;
					addCreatureReuse(cloneAndRandomizeCreature(*ptr));
					clonesCounter++;
				}
				if (wrapPos(&(*ptr)->pos))
				{
					(*ptr)->energy -= screenWrapPenality;
				}
				for (auto zone : zones) {
					zone->update((*ptr));
					for (auto plant : plants) {
						if (SDL_FPointInRect(&(*ptr)->pos,
								&plant->rect_food)) {
							if ((*ptr)->energy < 255 && plant->energy > 0) {
								(*ptr)->energy += (*ptr)->feed_factor
										* energryDelta * *timeDelta;
								plant->energy = plant->energy
										- ((*ptr)->feed_factor * energryDelta
												* *timeDelta);
								(*ptr)->neuralNet->kickFoodFoundFactor();
							}
						}
					}
				}
			}

			if (!(*ptr)->isAlive()) {
				for (auto zone : zones) {
					zone->kickOut(*ptr);
				}
				(*ptr) = nullptr;
				continue;
			}

		}
	}
	if (count > maxCount) {
		maxCount = count;
	}
	if (maxGen > maxGenEver) {
		maxGenEver = maxGen;
		maxCountAtMaxGenEver = count;
		maxScreenWrapPenalityAtMaxGenEver = screenWrapPenality;
		minEneryDeltaAtMaxGenEver = energryDelta;
	} else if (maxGen == maxGenEver) {
		if (count > maxCountAtMaxGenEver) {
			maxCountAtMaxGenEver = count;
		}
		if (screenWrapPenality > maxScreenWrapPenalityAtMaxGenEver) {
			maxScreenWrapPenalityAtMaxGenEver = screenWrapPenality;
		}
		if (energryDelta < minEneryDeltaAtMaxGenEver) {
			minEneryDeltaAtMaxGenEver = energryDelta;
		}
	}

	if (count > 50 && energryDelta > 0) {
		energryDelta -= (count-50) * 0.000000005;
//		screenWrapPenality += 0.005;
	}
	else {
		energryDelta += 0.000000005;
//		screenWrapPenality -= 0.005;
	}
	logger->setPermaLog("Size", to_string(count) + " (" + to_string(maxCount)+ ")");
	logger->setPermaLog("Vect size", to_string(creaturesWorld.size()));
	logger->setPermaLog("Time scale", to_string(settings->timeScale));
	logger->setPermaLog("Max Gen",
			to_string(maxGen) + "(max gen ever: " + to_string(maxGenEver)
					+ ", max cnt at max gen: " + to_string(maxCountAtMaxGenEver)
					+ ")");
	logger->setPermaLog("Max Gen st.",
						"max scr wrp pen: " + to_string(maxScreenWrapPenalityAtMaxGenEver)
						+ ", min energy delta: " + to_string(minEneryDeltaAtMaxGenEver)
						);
	logger->setPermaLog("CR cloned", to_string(clonesCounter));
	logger->setPermaLog("Enegry delta", to_string(energryDelta) + " (" + to_string(baseEnergryDelta) + ")");
	logger->setPermaLog("Screen wrap penality", to_string(screenWrapPenality) + " (" + to_string(baseScreenWrapPenality) + ")");

		for (auto plant : plants) {
			if (plant->energy < 1024.0) {
				plant->energy = plant->energy
						+ (energryDelta / count) * *timeDelta;
			}
			plant->update();
		}
	if (count < 5) {
		addCreature(SDL_Point { (rand() % 1000), (rand() % 1000) });
	} //TODO: Disabled for view map check
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
	if (settings->look) {
		for (auto ptr = creaturesWorld.begin(); ptr < creaturesWorld.end();
				ptr++) {
			auto creature = *ptr;
			if (creature != nullptr) {
				if (creature->isAlive()) {
					creature->cleanupView();
//					for (auto zone : zones) {
//					zone->update(creature);
						for (auto plant : plants) {
							if (plant != nullptr) {
								creature->lookAt(plant);
							}
//							creature->updateView();
//					if (distance(creature->pos, zone->pos) <= zone->size) {
//						for (auto otherCreature : *zone->creatures) {
//							if (otherCreature != nullptr) {
//								creature->lookAt(otherCreature);
//							}

//						}
						}
//					}
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
			for (auto zone : zones) {
				zone->update(plant);
			}
		}
	}
}

void World::updateNeuralNetworks() {
float avgHiddenLayerTreshold = 0.0;
float avgOutputLayerTreshold = 0.0;
int countt = 0;
	for (auto ptr = creaturesWorld.begin(); ptr < creaturesWorld.end(); ptr++) {
		auto creature = *ptr;
		if (creature != nullptr) {
			if (creature->isAlive()) {
				creature->updateNeuralNet(settings);
				countt++;
				avgHiddenLayerTreshold += creature->neuralNet->avgHiddenTreshhlold;
				avgOutputLayerTreshold += creature->neuralNet->avgOutputTreshhlold;
			}
		}
	}
	avgHiddenLayerTreshold = avgHiddenLayerTreshold / countt;
	avgOutputLayerTreshold = avgOutputLayerTreshold / countt;
	logger->setPermaLog("Max Gen neur st.",
			"avg hidden trsh: " + to_string(avgHiddenLayerTreshold)
					+ ", avg output trsh: "
					+ to_string(avgOutputLayerTreshold));
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

bool World::wrapPos(SDL_FPoint *pos) {
//	if (pos->x < 0) {
//		pos->x = SIZE_W + pos->x;
//		return true;
//	} else if (pos->x > SIZE_W) {
//		pos->x = pos->x - SIZE_W;
//		return true;
//	}
//	if (pos->y < 0) {
//		pos->y = SIZE_H + pos->y;
//		return true;
//	} else if (pos->y > SIZE_H) {
//		pos->y = pos->y - SIZE_H;
//		return true;
//	}
//	return false;
	if (pos->x < 0) {
		pos->x = 0;
		return true;
	} else if (pos->x > SIZE_W) {
		pos->x = SIZE_W;
		return true;
	}
	if (pos->y < 0) {
		pos->y = 0;
		return true;
	} else if (pos->y > SIZE_H) {
		pos->y = SIZE_H;
		return true;
	}
	return false;
}
