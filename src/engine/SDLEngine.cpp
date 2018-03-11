/*
 * Engine.cpp
 *
 *  Created on: 11 mar 2018
 *      Author: Kamil
 */

#include "SDLEngine.h"

SDLEngine::SDLEngine() {
    // TODO Auto-generated constructor stub

}

SDLEngine::~SDLEngine() {
    // TODO Auto-generated destructor stub
}

bool SDLEngine::init() {
    bool success = true;
    //TODO: This should not be here
    imageSurface = SDL_LoadBMP("res/hello_world.bmp");
    SDL_SetColorKey(imageSurface, SDL_TRUE,
            SDL_MapRGB(imageSurface->format, 0, 255, 255));

    if (imageSurface == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n",
                "res/hello_world.bmp", SDL_GetError());
        success = false;
    }

    if (SDL_Init( SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        window = SDL_CreateWindow("unGame", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("Window could not be created! SDL_Error: %s\n",
                    SDL_GetError());
            success = false;
        } else {
            screenSurface = SDL_GetWindowSurface(window);
        }
    }
    return success;
}
void SDLEngine::run(World world) {
    while (isRunning) {
        while (SDL_PollEvent(&ev) != 0) {
            if (ev.type == SDL_QUIT)
                isRunning = false;
        }
        SDL_UpdateWindowSurface(window);
    }
}
void SDLEngine::close() {
    //TODO: this should not be here
    SDL_FreeSurface(imageSurface);
    imageSurface = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}
