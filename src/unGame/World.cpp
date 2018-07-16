#include <World.h>
#include <iostream>
#include <stdio.h>

World::World() {
  creatures = new std::vector<Creature*>();
  std::srand(time(nullptr));
  settings = nullptr;
}

World::~World() {
  SDL_FreeSurface(backgroundTexture);
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

