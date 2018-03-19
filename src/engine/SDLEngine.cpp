/*
 * Engine.cpp
 *
 *  Created on: 11 mar 2018
 *      Author: Kamil
 */

#include <iostream>
#include <chrono>

#include "SDLEngine.h"

bool SDLEngine::init() {
    bool success = true;
    if (SDL_Init( SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        window = SDL_CreateWindow("unGame", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            printf("Window could not be created! SDL_Error: %s\n",
                    SDL_GetError());
            success = false;
        } else {
            screenSurface = SDL_GetWindowSurface(window);
        }
    }
    using namespace std::chrono;
    frameTimeDelta = duration_cast<milliseconds>(
            system_clock::now().time_since_epoch());
    return (success);
}
void SDLEngine::run(World * world) {
    while (isRunning) {
        SdlEventHandler.handleEvents(&isRunning);

        SDL_FillRect(screenSurface, nullptr, 0);
        world->updateAndDraw(countFrameTimeDelta(), screenSurface);
        SDL_UpdateWindowSurface(window);
        countFPS();
    }
}
void SDLEngine::close() {
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_Quit();
}

void SDLEngine::countFPS() {
    using namespace std::chrono;
    msEnd = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    if ((msEnd - msStart).count() > 1000) {
        msStart = duration_cast<milliseconds>(
                system_clock::now().time_since_epoch());
        std::cout << "FPS: " << frame_counter << std::endl;
        frame_counter = 0;
    } else {
        ++frame_counter;
    }
}

long SDLEngine::countFrameTimeDelta() {
    using namespace std::chrono;
    std::chrono::milliseconds result = duration_cast<milliseconds>(
            system_clock::now().time_since_epoch()) - frameTimeDelta;
    if ( isFPSLimitEnabled && result.count() < (1000.0/fpsLimit)) {
        SDL_Delay(1);
        return (countFrameTimeDelta());
    } else {
        frameTimeDelta = duration_cast<milliseconds>(
                system_clock::now().time_since_epoch());
        return (result.count());
    }
}
