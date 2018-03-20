/*
 * Engine.cpp
 *
 *  Created on: 11 mar 2018
 *      Author: Kamil
 */

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
    frameTimeDelta = SDL_GetTicks();
    return (success);
}
void SDLEngine::run(World * world) {
    using namespace std::chrono;
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
    msEnd = SDL_GetTicks();
    if ((msEnd - msStart) > 1000) {
        msStart = SDL_GetTicks();
        std::cout << "FPS: " << frame_counter << std::endl;
        frame_counter = 0;
    } else {
        ++frame_counter;
    }
}

uint32_t SDLEngine::countFrameTimeDelta() {

    frameTimeDeltaTemp = SDL_GetTicks() - frameTimeDelta;
    if (isFPSLimitEnabled && frameTimeDeltaTemp < (1000.0 / fpsLimit)) {
        SDL_Delay(1);
        return (countFrameTimeDelta());
    } else {
        frameTimeDelta = SDL_GetTicks();
        return (frameTimeDeltaTemp);
    }
}
