#include <SDL2/SDL.h>
#include <stdio.h>
#include <UNGLogger.h>
#include <iostream>

#include "unGame.h"

int main(int argc, char *args[]) {
	settings = new Settings();
	auto console = LoggingHandler::getConsole();
	auto logger = LoggingHandler::getLogger("MAIN");
	logger->log("Start world generator");
	worldGenerator = new WorldGenerator();
	logger->log("Generate world");
//
//	world = worldGenerator->generateWorld(WorldGenerator::conf1Creature);
//  world = worldGenerator->generateWorld(WorldGenerator::conf2CreatureSightTest);
//	world = worldGenerator->generateWorld(WorldGenerator::conf99RandomCreatures);
  world = worldGenerator->generateWorld(WorldGenerator::conf1KRandomCreatures);
//	world = worldGenerator->generateWorld(
//			WorldGenerator::conf10KRandomCreatures);
//	world->logger = &console->logqueue;
//
	logger->log("World set settings");
	world->setSettings(settings);
	logger->log("Starting");
	ungEngine.run(world);
	sdlEngine.run(world, settings);
//	sdlEngine.logger = ;
	console->run();
	sdlEngine.stop();
	ungEngine.close();
	logger->log("Removing world...");
	delete (world);
	logger->log("Removing world generator");
	delete (worldGenerator);
	logger->log("Removing settings handler");
	delete (settings);
	logger->log("Closed");
	console->close();
	delete console;
	return 0;
}
