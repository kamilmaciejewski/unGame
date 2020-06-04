#include "UNGGeometry.h"
#include "UNGWorldGenerator.h"
#include "UNGLoggingHandler.h"


WorldGenerator::WorldGenerator() {
}

WorldGenerator::~WorldGenerator() {
}

World* WorldGenerator::generateWorld(TestConfigurations testConfiguration) {
	World *tmpWorld = new World();
	gereratePlantsCircle(tmpWorld);
	NeuralParams params(&tmpWorld->generator, &tmpWorld->distribution);

	if (testConfiguration == conf2CreatureSightTest) {
		Creature *observer = new Creature(tmpWorld->surface, params);
		float speedZero2 = 0.05;
		float speedZero = 0.0;
		observer->setPos(SDL_FPoint { (float) 300, (float) 300 });
		observer->rotate(270);
		observer->setSpeed(speedZero2);
		observer->setRotationSpeed(speedZero);
		observer->setActive();
		tmpWorld->addCreature(observer);

//		Creature *traveller = new Creature(tmpWorld->surface);
//		float speed = 0.4;
//		traveller->setPos(
//				SDL_FPoint { (float) UNG_Globals::SCREEN_W / 2, (float) UNG_Globals::SCREEN_H / 2 });
//		traveller->rotate(0);
//		traveller->setSpeed(speed);
//		traveller->setRotationSpeed(speed);
//		traveller->setInactive();
//		tmpWorld->addCreature(traveller);

	} else {

		for (int i = 0; i < testConfiguration; ++i) {
			tmpWorld->addCreature(
					generateCreature(testConfiguration, tmpWorld->surface, tmpWorld));
		}
	}
	return (tmpWorld);
}

Creature* WorldGenerator::generateCreature(
		TestConfigurations &testConfiguration, SDL_Surface *surface, World* world) {

	NeuralParams params(&world->generator, &world->distribution);
	params.randomize();
	Creature *tmpCreature = new Creature(surface, params);
	tmpCreature->setSpeed(fabs(world->distribution(world->generator)));

	switch (testConfiguration) {

	case conf1Creature:
		tmpCreature->setPos(SDL_FPoint { 500.0, 500.0 });
		tmpCreature->rotate(0);
		break;
	case conf2CreatureSightTest:
		break;
	case conf99RandomCreatures:
		tmpCreature->setPos(getRandomPos());
		tmpCreature->rotate(rand() % 359);
		break;
	case conf1KRandomCreatures:
		tmpCreature->setPos(getRandomPos());
		tmpCreature->rotate(rand() % 359);
		break;
	case conf10KRandomCreatures:
		tmpCreature->setPos(getRandomPos());
		tmpCreature->rotate(rand() % 359);
		break;
	}
	return (tmpCreature);
}

float WorldGenerator::getRandomPosH() {
	return (float) (UNG_Globals::SCREEN_H / 2
			+ rand() % UNG_Globals::SCREEN_H / 10);
}

float WorldGenerator::getRandomPosW() {
	return (float) (UNG_Globals::SCREEN_W / 2
			+ rand() % UNG_Globals::SCREEN_W / 10);
}

SDL_FPoint WorldGenerator::getRandomPos() {
	return SDL_FPoint { (float) getRandomPosW(), (float) getRandomPosH() };
}
float WorldGenerator::getRandomSpeed() {
	return ((0.0001 * (rand() % 2000)));
}
float WorldGenerator::getRandomAlpha() {
	return (10 + (rand() % 150));
}

void WorldGenerator::gereratePlantsCircle(World* world){
	int n = 20;
	int xs = UNG_Globals::worldBox.w/2;
	int ys = UNG_Globals::worldBox.h/2;
	int r = 300;

	for(int i = 0; i < n; i++)
	{
	  double alpha = 6.283185 * i / (n);

	  int x = (int)(xs + r * cos(alpha));
	  int y = (int)(ys + r * sin(alpha));
	  world->addPlant({x,y});
	}


}
