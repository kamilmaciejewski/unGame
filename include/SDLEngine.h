/*
 * engine.h
 *
 *  Created on: 11 mar 2018
 *      Author: Kamil
 */

#ifndef SDLENGINE_H_
#define SDLENGINE_H_

#include <chrono>
#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>

#include "SDL2_rotozoom.h"
#include "World.h"
#include "SDLEventHandler.h"

class SDLEngine {
    SDLEventHandler SdlEventHandler;
    bool isRunning = true;
    bool isFPSLimitEnabled = true;
    int fpsLimit = 200;
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    int frame_counter = 0;

    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;
    uint32_t frameTimeDelta, frameTimeDeltaTemp, msStart,
            msEnd;

    void countFPS();
    uint32_t countFrameTimeDelta();

public:
    bool init();
    void close();
    void run(World *);
};

#endif /* SDLENGINE_H_ */
