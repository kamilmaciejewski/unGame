/*
 * SDLEventHandler.h
 *
 *  Created on: 11 mar 2018
 *      Author: Kamil
 */

#ifndef SDLEVENTHANDLER_H_
#define SDLEVENTHANDLER_H_

#include <SDL2/SDL.h>

class SDLEventHandler {
    SDL_Event ev;

public:
    void handleEvents(bool*);
};

#endif /* SDLEVENTHANDLER_H_ */
