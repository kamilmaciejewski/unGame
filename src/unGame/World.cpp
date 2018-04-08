#include <World.h>
#include <iostream>
#include <stdio.h>

World::World() {
  creatures = new std::vector<Creature*>();
  std::srand(time(nullptr));
}

World::~World() {
  SDL_FreeSurface(backgroundTexture);
  for (auto creature : *creatures) {
    if (creature != nullptr) {
      delete (creature);
    } else {
      std::cout << "Null, skip." << std::endl;
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
    creature->draw(renderer, screenWidht, screenHeight);
  }
}
void World::update(uint32_t* timeDelta) {
  for (auto creature : *creatures) {
    creature->update(timeDelta);
  }
}

SDL_bool World::checkPos(SDL_Point mousePos) {
  for (auto creature : *creatures) {
  if (SDL_PointInRect(&mousePos, &creature->rect_pos)) {
        std::cout << "Cont";
        return (SDL_TRUE);
      }
    }
    return (SDL_FALSE);
  }

