#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "unGame.h"
#include "SDLEngine.h"

int main(int argc, char* args[]) {
  settings = new Settings();
  if(!engine.init(settings)){
	  std::cout<<"Init failed"<<std::endl;
	  return 1;
  };
  worldGenerator = new WorldGenerator();

//  world = worldGenerator->generateWorld(WorldGenerator::conf1Creature);
//  world = worldGenerator->generateWorld(WorldGenerator::conf2CreatureSightTest);
  world = worldGenerator->generateWorld(WorldGenerator::conf99RandomCreatures);
//  world = worldGenerator->generateWorld(WorldGenerator::conf1KRandomCreatures);
//  world = worldGenerator->generateWorld(WorldGenerator::conf10KRandomCreatures);

  world->setSettings(settings);
  engine.run(world);
  engine.close();

  delete (world);
  delete (worldGenerator);
  delete (settings);
  return (0);
}
