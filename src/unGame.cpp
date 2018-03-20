#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "unGame.h"
#include "SDLEngine.h"

int main(int argc, char* args[]) {
    SDLEngine engine;
    engine.init();
    worldGenerator = new WorldGenerator();
    World * world = worldGenerator->generateWorld(
            WorldGenerator::conf99RandomCreatures);
    engine.run(world);
    engine.close();
    delete (world);
    return (0);
}
