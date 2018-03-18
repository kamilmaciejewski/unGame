#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "rotozoom/SDL2_rotozoom.h"
#include "include/unGame.h"
#include "engine/SDLEngine.h"

int main(int argc, char* args[]) {
    SDLEngine engine;
    engine.init();
    engine.run(world);
    engine.close();
    return (0);
}
