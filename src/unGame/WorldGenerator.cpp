#include "WorldGenerator.h"
#include <cstdlib>
#include <ctime>
#include "SDLEngine.h"
#include "Geometry.hpp"

WorldGenerator::WorldGenerator() {
	std::srand(time(nullptr));
}

WorldGenerator::~WorldGenerator() {
}

World* WorldGenerator::generateWorld(TestConfigurations testConfiguration) {
	World *tmpWorld = new World();
	if (testConfiguration == conf2CreatureSightTest) {
		Creature *observer = new Creature(tmpWorld->surface);
		float speedZero2 = 0.2;
		float speedZero = 0.0;
		observer->setPos(
				SDL_FPoint { (float) SCREEN_WIDTH / 2, (float) SCREEN_HEIGHT / 2 });
		observer->rotate(270);
		observer->setSpeed(speedZero2);
		observer->setRotationSpeed(speedZero);
		observer->setAlpha(255);
		observer->setActive();
		tmpWorld->addCreature(observer);

		Creature *traveller = new Creature(tmpWorld->surface);
		float speed = 0.4;
		traveller->setPos(
				SDL_FPoint { (float) SCREEN_WIDTH / 2, (float) SCREEN_HEIGHT / 2 });
		traveller->rotate(0);
		traveller->setSpeed(speed);
		traveller->setRotationSpeed(speed);
		traveller->setAlpha(255);
		traveller->setInactive();
		tmpWorld->addCreature(traveller);

	} else {

		for (int i = 0; i < testConfiguration; ++i) {
			tmpWorld->addCreature(
					generateCreature(testConfiguration, tmpWorld->surface));
		}
	}
	return (tmpWorld);
}

Creature* WorldGenerator::generateCreature(
		TestConfigurations &testConfiguration, SDL_Surface *surface) {
	Creature *tmpCreature = new Creature(surface);

	float speed = 0.05;
	float speedZero = 0;
	float speed0 = (0.1 + (rand() % 6) * 0.09);
	float speed1 = (0.1 + (rand() % 1000) * 0.0003);

	float rotSpeed1 = (0.1 + (0.01 * (rand() % 20)));
	float rotSpeed2 = (0.1 + (0.00001 * (rand() % 20000)));

	switch (testConfiguration) {
	case conf1Creature:
		tmpCreature->setPos(SDL_FPoint { 100.0, 100.0 });
		tmpCreature->rotate(0);
		tmpCreature->setSpeed(speedZero);
		tmpCreature->setRotationSpeed(speed);
		tmpCreature->setAlpha(255);
		break;
	case conf2CreatureSightTest:
		break;
	case conf99RandomCreatures:
		tmpCreature->setPos(getRandomPos());
		tmpCreature->rotate(rand() % 359);
		tmpCreature->setSpeed(speed0);
		tmpCreature->setRotationSpeed(speedZero);
		tmpCreature->setAlpha(rand() % 150);
		break;
	case conf1KRandomCreatures:
		tmpCreature->setPos(getRandomPos());
		tmpCreature->rotate(rand() % 359);
		tmpCreature->setSpeed(speed1);
		speedZero = getRandomSpeed();
		tmpCreature->setRotationSpeed(speedZero);
		tmpCreature->setAlpha(rand() % 150);
		break;
	case conf10KRandomCreatures:
		tmpCreature->setPos(getRandomPos());
		tmpCreature->rotate(rand() % 359);
		tmpCreature->setSpeed(speed1);
		tmpCreature->setRotationSpeed(speedZero);
		tmpCreature->setAlpha(rand() % 150);
		break;
	}
	return (tmpCreature);
}

float WorldGenerator::getRandomPosH() {
	return (float) (SCREEN_HEIGHT / 2 + rand() % SCREEN_HEIGHT / 10);
}

float WorldGenerator::getRandomPosW() {
	return (float) (SCREEN_WIDTH / 2 + rand() % SCREEN_WIDTH / 10);
}

SDL_FPoint WorldGenerator::getRandomPos() {
	return SDL_FPoint { (float) getRandomPosW(), (float) getRandomPosH() };
}
float WorldGenerator::getRandomSpeed(){
	return ((0.0001 * (rand() % 2000)));
}
