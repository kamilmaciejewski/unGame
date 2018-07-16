#ifndef WORLD_H_
#define WORLD_H_

#include <SDL2/SDL.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "Creature.h"

class World {

  SDL_Surface* backgroundTexture = nullptr;
  Settings* settings;
  std::vector<Creature*> * creatures;
public:

  SDL_bool checkPos(SDL_Point);
  void draw(SDL_Renderer*, int*, int*);
  World();
  virtual ~World();
  void addCreature(Creature *);
  void update(uint32_t*);
  void setSettings(Settings*);
  SDL_Surface* surface;
};

#endif /* WORLD_H_ */
