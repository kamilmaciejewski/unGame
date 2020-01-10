#include <World.h>
#include <iostream>
#include <stdio.h>

World::World() {
  surface = SDL_LoadBMP("res/arrow.bmp");
  SDL_SetColorKey(surface, SDL_TRUE,
      SDL_MapRGB(surface->format, 0xff, 0x0, 0xff));
  if (surface == nullptr) {
    printf("Unable to load image: %s\n", SDL_GetError());
  }
  creatures = new std::vector<Creature*>();
  std::srand(time(nullptr));
  settings = nullptr;
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
}

void World::addCreature(Creature* creature) {

  creatures->push_back(creature);
}
//TODO: Last two parameters should be a rectangle for zooming the screen.
void World::draw(SDL_Renderer* renderer) {
  for (auto creature : *creatures) {
    creature->draw(renderer, settings);
  }
}
void World::update(uint32_t* timeDelta) {
  for (auto creature : *creatures) {
    creature->update(timeDelta, settings);
  }
}

void World::setSettings(Settings* _settings) {
  settings = _settings;
}

void World::markActiveObjectByMousePos(SDL_Point mousePos) {
  for (auto creature : *creatures) {
    if (SDL_PointInRect(&mousePos, &creature->getDrawable()->rect_pos)) {
      creature->isActive = true;
      infoStr = creature->getInfo();
      return;
    } else {
      creature->isActive = false;
    }
  }
  infoStr = "none";
}

