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
    float speedZero = 0;
    float speed0 = (0.1 + (rand() % 6) * 0.05);
    float speed1 = (0.1 + (rand() % 1000) * 0.0003);

    float rotSpeed1 = (0.1 + (0.01 * (rand() % 20)));
    float rotSpeed2 = (0.1 + (0.00001 * (rand() % 20000)));

    switch (testConfiguration) {
  case conf1Creature:
    tmpCreature->setPos(100, 100);
    tmpCreature->rotate(0);
    tmpCreature->setSpeed(speedZero);
    tmpCreature->setRotationSpeed(speed);
    tmpCreature->setAlpha(255);
    break;
  case conf99RandomCreatures:
    tmpCreature->setPos(std::rand() % SCREEN_WIDTH,
        std::rand() % SCREEN_HEIGHT);
    tmpCreature->rotate(rand() % 359);
    tmpCreature->setSpeed(speed0);
    tmpCreature->setRotationSpeed(rotSpeed1);
    tmpCreature->setAlpha(rand()%150);
    break;
  case conf1KRandomCreatures:
    tmpCreature->setPos(getRandomPosW(),getRandomPosH());
    tmpCreature->rotate(rand() % 359);
    tmpCreature->setSpeed(speed1);
    tmpCreature->setRotationSpeed(rotSpeed2);
    tmpCreature->setAlpha(rand()%150);
    break;
  case conf10KRandomCreatures:
      tmpCreature->setPos(getRandomPosW(),getRandomPosH());
      tmpCreature->rotate(rand() % 359);
      tmpCreature->setSpeed(speed1);
      tmpCreature->setRotationSpeed(rotSpeed2);
      tmpCreature->setAlpha(rand()%150);
      break;
  }
  return (tmpCreature);
}

int WorldGenerator::getRandomPosH(){
	return SCREEN_HEIGHT/2 + rand() % SCREEN_HEIGHT/10;
}

int WorldGenerator::getRandomPosW(){
	return SCREEN_WIDTH/2 + rand() % SCREEN_WIDTH/10;
}
