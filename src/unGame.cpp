#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "unGame.h"

int main(int argc, char *args[]) {
	settings = new Settings();
	if (!sdlEngine.init(settings)) {
		std::cout << "Init failed" << std::endl;
		return 1;
	}
	std::cout << "Start world generator" << std::endl;
	worldGenerator = new WorldGenerator();
	std::cout << "Generate world" << std::endl;
//
//	world = worldGenerator->generateWorld(WorldGenerator::conf1Creature);
//  world = worldGenerator->generateWorld(WorldGenerator::conf2CreatureSightTest);
//	world = worldGenerator->generateWorld(WorldGenerator::conf99RandomCreatures);
//  world = worldGenerator->generateWorld(WorldGenerator::conf1KRandomCreatures);
  world = worldGenerator->generateWorld(WorldGenerator::conf10KRandomCreatures);
//
	std::cout << "World set settings" << std::endl;
	world->setSettings(settings);
	std::cout << "Starting" << std::endl;
	ungEngine.run(world);
	sdlEngine.run(world);
	sdlEngine.close();
	ungEngine.close();
	std::cout << "Removing world..." << std::endl;
	delete (world);
	std::cout << "Removing world generator" << std::endl;
	delete (worldGenerator);
	std::cout<<"Removing settings handler"<<std::endl;
	delete (settings);
	std::cout << "Closed" << std::endl;
	return 0;
}
