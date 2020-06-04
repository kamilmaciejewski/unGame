#ifndef WORLDGENERATOR_H_
#define WORLDGENERATOR_H_

#include <random>
#include <UNGWorld.h>
#include <cstdlib>
#include "SDLEngine.h"
#include "UNGGlobals.h"

class WorldGenerator {
public:
  enum TestConfigurations {
    conf1Creature = 1,
	conf2CreatureSightTest = 2,
    conf99RandomCreatures = 99,
    conf1KRandomCreatures = 1000,
    conf10KRandomCreatures = 10000,
  };

  WorldGenerator();
  virtual ~WorldGenerator();
  World* generateWorld(TestConfigurations);
  Creature * generateCreature(TestConfigurations &, SDL_Surface*, World*);
  float getRandomPosH();
  float getRandomPosW();
  SDL_FPoint getRandomPos();
  float getRandomSpeed();
  float getRandomAlpha();
private:
	void gereratePlantsCircle(World*);

};

#endif /* WORLDGENERATOR_H_ */
