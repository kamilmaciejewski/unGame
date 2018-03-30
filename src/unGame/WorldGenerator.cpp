#include "WorldGenerator.h"
#include <cstdlib>
#include <ctime>
#include "SDLEngine.h"

WorldGenerator::WorldGenerator() {
  std::srand(time(nullptr));
}

WorldGenerator::~WorldGenerator() {
}

World* WorldGenerator::generateWorld(TestConfigurations testConfiguration) {
  World * tmpWorld = new World();

  for (int i = 0; i < testConfiguration; ++i) {
    tmpWorld->addCreature(generateCreature(testConfiguration));
  }
  return (tmpWorld);
}

Creature * WorldGenerator::generateCreature(
    TestConfigurations & testConfiguration) {
  Creature * tmpCreature = new Creature();

  switch (testConfiguration) {
  case conf1Creature:
    tmpCreature->setPos(320, 320);
    tmpCreature->rotate(0);
    tmpCreature->setSpeed(0.06);
    tmpCreature->setRotationSpeed(0.01);
    break;
  case conf99RandomCreatures:
    tmpCreature->setPos(std::rand() % SCREEN_WIDTH,
        std::rand() % SCREEN_HEIGHT);
    tmpCreature->rotate(rand() % 359);
    tmpCreature->setSpeed((0.3 + (rand() % 6) * 0.05));
    tmpCreature->setRotationSpeed(0.1 + (0.01 * (rand() % 20)));
    break;
  case conf10000RandomCreatures:
    tmpCreature->setPos((rand() % (SCREEN_WIDTH + 100)),
        (rand() % (SCREEN_HEIGHT + 100)));
    tmpCreature->setPos(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
    tmpCreature->rotate(rand() % 359);
    tmpCreature->setSpeed((0.3 + (rand() % 10) * 0.05));
    tmpCreature->setRotationSpeed(0.1 + (0.01 * (rand() % 20)));
    break;
    break;
  }
  return (tmpCreature);
}

