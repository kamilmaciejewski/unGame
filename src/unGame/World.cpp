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
	//TODO: Globalize values
	int SCREEN_WIDTH = 1920;
	int SCREEN_HEIGHT = 1080;
	int zonesizeX = SCREEN_WIDTH / zoneRes;
	int zonesizeY = SCREEN_HEIGHT / zoneRes;
	for (int x = 0; x <= SCREEN_WIDTH; x += zonesizeX) {
		for (int y = 0; y <= SCREEN_HEIGHT; y += zonesizeY) {
			zones->push_back(new Zone(x, y));
		}
	}

}

void World::addCreature(Creature *creature) {
	creatures->push_back(creature);
}
//TODO: Last two parameters should be a rectangle for zooming the screen.
void World::draw(SDL_Renderer *renderer) {
	for (auto creature : *creatures) {
		creature->draw(renderer, settings);
	}
	for (auto zone : *zones) {
		zone->draw(renderer);
	}
}
void World::update(uint32_t *timeDelta) {
	for (auto creature : *creatures) {
		creature->update(timeDelta, settings);
		if (creature->isActive()) {
			infoStr = creature->getInfo();
		}
	}
}

void World::updateViewSense() {
	if (settings->look) {
		for (auto creature : *creatures) {
			for (auto vect : *creature->multiview) {
				delete (vect);
			}
			creature->multiview->clear();
			for (auto zone : *zones) {
				zone->update(creature);
				if (distance(creature->pos, zone->pos) <= zone->size) {
//					for (auto otherCreature : * creatures){
					for (auto otherCreature : *zone->creatures) {
//						if (
							creature->lookAt(otherCreature);
//								) {
//							break;
					}
				}
			}
		}
	}
}

void World::setSettings(Settings *_settings) {
	settings = _settings;
}

void World::markActiveObjectByMousePos(SDL_Point mousePos) {
	if (settings->mark_active == true) {
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

