#include "UNGame.h"

UNGame::UNGame(Settings *settings) {
	logger = LoggingHandler::getLogger("unGame");
	this->settings = settings;
}

UNGame::~UNGame() {
	delete logger;
	logger = nullptr;
	delete world;
//	world = nullptr;
}

void UNGame::run() {
	WorldGenerator generator;
	world = generator.generateWorld(
			WorldGenerator::TestConfigurations::conf99RandomCreatures);
	world->setSettings(settings);
	MultiEngine multiEngine;
	ungEngine.run(world);
	sdlEngine.run(world, settings);
	neuralEngine.run(world);
}
void UNGame::stop() {
	ungEngine.close();
	sdlEngine.stop();
	neuralEngine.close();
}
