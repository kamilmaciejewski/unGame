#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "unGame.h"

int main(int argc, char *args[]) {
	settings = new Settings();
	auto console = new UNGConsole();

	console->logqueue.push("Start world generator");
	worldGenerator = new WorldGenerator();
	console->logqueue.push("Generate world");
//
//	world = worldGenerator->generateWorld(WorldGenerator::conf1Creature);
//  world = worldGenerator->generateWorld(WorldGenerator::conf2CreatureSightTest);
//	world = worldGenerator->generateWorld(WorldGenerator::conf99RandomCreatures);
  world = worldGenerator->generateWorld(WorldGenerator::conf1KRandomCreatures);
//	world = worldGenerator->generateWorld(
//			WorldGenerator::conf10KRandomCreatures);
	world->logger = &console->logqueue;
//
	console->logqueue.push("World set settings");
	world->setSettings(settings);
	console->logqueue.push("Starting");
	ungEngine.run(world);
	sdlEngine.run(world, settings);
	sdlEngine.logger = &console->logqueue;
	console->run();
	sdlEngine.stop();
	ungEngine.close();
	console->logqueue.push("Removing world...");
	delete (world);
	console->logqueue.push("Removing world generator");
	delete (worldGenerator);
	console->logqueue.push("Removing settings handler");
	delete (settings);
	console->logqueue.push("Closed");
	console->close();
	delete console;
	return 0;
}
