#include "WorldGenerator.h"

WorldGenerator::WorldGenerator() {

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
    tmpCreature->setPos(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
    tmpCreature->rotate(rand() % 359);
    tmpCreature->setSpeed((0.3 + (rand() % 6) * 0.05));
    tmpCreature->setRotationSpeed(0.1 + (0.01 * (rand() % 20)));
    break;
  case conf1000RandomCreatures:
    break;
  }
  return (tmpCreature);
}

