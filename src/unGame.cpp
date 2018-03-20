#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "unGame.h"

int main(int argc, char* args[]) {
    SDLEngine engine;
    engine.init();
    world = new World();
    engine.run(world);
    engine.close();
    delete (world);
    return (0);
}
