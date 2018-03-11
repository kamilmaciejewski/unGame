/*
 * engine.h
 *
 *  Created on: 11 mar 2018
 *      Author: Kamil
 */

#ifndef SDLENGINE_H_
#define SDLENGINE_H_

#include <SDL2/SDL.h>
#include <stdio.h>
#include "../rotozoom/SDL2_rotozoom.h"
#include "../unGame/World.h"

class SDLEngine {
    SDL_Event ev;
    bool isRunning = true;
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;

    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    SDL_Surface* imageSurface = NULL;

public:
    SDLEngine();
    virtual ~SDLEngine();
    bool init();
    void close();
    void run(World world);
};

#endif /* SDLENGINE_H_ */
