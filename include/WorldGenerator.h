#ifndef WORLDGENERATOR_H_
#define WORLDGENERATOR_H_

#include "World.h"

class WorldGenerator {
  int SCREEN_WIDTH = 1920;
  int SCREEN_HEIGHT = 1080;
public:
  enum TestConfigurations {
    conf1Creature = 1,
    conf99RandomCreatures = 99,
    conf10KRandomCreatures = 10000,
  };

  WorldGenerator();
  virtual ~WorldGenerator();
  World* generateWorld(TestConfigurations);
  Creature * generateCreature(TestConfigurations &, SDL_Surface*);
};

#endif /* WORLDGENERATOR_H_ */
