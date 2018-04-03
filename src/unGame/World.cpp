#include <World.h>
#include <iostream>

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
void World::updateAndDraw(uint32_t* timeDelta, SDL_Renderer* renderer, int* screenWidht, int* screenHeight) {
  for (auto creature : *creatures) {
    creature->update(timeDelta);
    creature->draw(renderer, screenWidht, screenHeight);
  }

}

