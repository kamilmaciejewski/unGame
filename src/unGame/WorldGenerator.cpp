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
    tmpWorld->addCreature(
        generateCreature(testConfiguration, tmpWorld->surface));
  }
  return (tmpWorld);
}

Creature * WorldGenerator::generateCreature(
    TestConfigurations & testConfiguration, SDL_Surface* surface) {
  Creature * tmpCreature = new Creature(surface);

    float speed = 0.05;
    float speed0 = (0.1 + (rand() % 6) * 0.05);
    float speed1 = (0.3 + (rand() % 10000) * 0.00005);
      float speed2 = (0.3 + (rand() % 10000) * 0.00005);

    switch (testConfiguration) {
  case conf1Creature:
    tmpCreature->setPos(100, 100);
    tmpCreature->rotate(0);
    tmpCreature->setSpeed(speed);
    tmpCreature->setRotationSpeed(0.05);
    break;
  case conf99RandomCreatures:
    tmpCreature->setPos(std::rand() % SCREEN_WIDTH,
        std::rand() % SCREEN_HEIGHT);
    tmpCreature->rotate(rand() % 359);
    tmpCreature->setSpeed(speed0);
    tmpCreature->setRotationSpeed(0.1 + (0.01 * (rand() % 20)));
    break;
  case conf1KRandomCreatures:
    tmpCreature->setPos((rand() % SCREEN_WIDTH), (rand() % SCREEN_HEIGHT));
    tmpCreature->rotate(rand() % 359);
    tmpCreature->setSpeed(speed1);
    tmpCreature->setRotationSpeed(0.1 + (0.00001 * (rand() % 20000)));
    break;
  case conf10KRandomCreatures:
      tmpCreature->setPos((rand() % SCREEN_WIDTH), (rand() % SCREEN_HEIGHT));
      tmpCreature->rotate(rand() % 359);
      tmpCreature->setSpeed(speed2);
      tmpCreature->setRotationSpeed(0.1 + (0.00001 * (rand() % 20000)));
      break;
  }
  return (tmpCreature);
}

