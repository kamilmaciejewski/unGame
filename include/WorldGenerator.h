#ifndef WORLDGENERATOR_H_
#define WORLDGENERATOR_H_

#include "World.h"
#include "Constants.h"

class WorldGenerator {
public:
  enum TestConfigurations {
    conf1Creature = 1,
    conf99RandomCreatures = 99,
    conf1000RandomCreatures = 1000,
  };

  WorldGenerator();
  virtual ~WorldGenerator();
  World* generateWorld(TestConfigurations);
  Creature * generateCreature(TestConfigurations &);
};

#endif /* WORLDGENERATOR_H_ */
