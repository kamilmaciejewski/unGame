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
  delete (&creatures);
}

void World::addCreature(Creature* creature) {

  creatures->push_back(creature);
}
//TODO: Last two parameters should be a rectangle for zooming the screen.
void World::draw(SDL_Renderer* renderer, int* screenWidht, int* screenHeight) {
  for (auto creature : *creatures) {
    creature->draw(renderer, screenWidht, screenHeight, settings);
  }
}
void World::update(uint32_t* timeDelta) {
  for (auto creature : *creatures) {
    creature->update(timeDelta);
  }
}

void World::setSettings(Settings* _settings){
  settings = _settings;
}

SDL_bool World::checkPos(SDL_Point mousePos) {
  for (auto creature : *creatures) {
    if (SDL_PointInRect(&mousePos, &creature->rect_pos)) {
      creature->isActive = true;
      return (SDL_TRUE);
    } else {
      creature->isActive = false;
    }
  }
  return (SDL_FALSE);
}

