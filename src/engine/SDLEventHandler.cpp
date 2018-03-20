/*
 * SDLEventHandler.cpp
 *
 *  Created on: 11 mar 2018
 *      Author: Kamil
 */

#include "SDLEventHandler.h"

void SDLEventHandler::handleEvents(bool* result) {
    while (SDL_PollEvent(&ev) != 0) {
        if (ev.type == SDL_QUIT)
            *result = false;
    }
}

