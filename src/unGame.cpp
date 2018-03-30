#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "unGame.h"
#include "SDLEngine.h"

int main(int argc, char* args[]) {
  engine.init();
  worldGenerator = new WorldGenerator();
//  world = worldGenerator->generateWorld(WorldGenerator::conf99RandomCreatures);
    world = worldGenerator->generateWorld(WorldGenerator::conf10000RandomCreatures);
  engine.run(world);
  engine.close();
  delete (world);
  return (0);
}
