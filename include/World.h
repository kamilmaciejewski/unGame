#ifndef WORLD_H_
#define WORLD_H_

#include <SDL2/SDL.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "Creature.h"

class World {

  SDL_Surface* backgroundTexture = nullptr;
public:
  World();
  virtual ~World();
  void addCreature(Creature *);
  void draw(SDL_Renderer*, int*, int*);
  SDL_bool checkPos(SDL_Point);
  void update(uint32_t*);
  std::vector<Creature*> * creatures;
};

#endif /* WORLD_H_ */
