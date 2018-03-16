/*
 * player.cpp
 *
 *  Created on: 9 mar 2018
 *      Author: Kamil
 */

#include "Creature.h"
#include <stdio.h>
#include <SDL2/SDL.h>

Creature::Creature() {
    surface = SDL_LoadBMP("res/arrow.bmp");
    optimizedSurface = SDL_ConvertSurface(surface, surface->format, 0);
    SDL_FreeSurface(surface);

    if (surface == NULL) {
        printf("Unable to load image: %s\n", SDL_GetError());
    }
    rotAngle = 0;
    posX = 0;
    posY = 0;
}

Creature::~Creature() {
}

void Creature::draw(SDL_Surface* destSurface) {
    updatePos();
    SDL_BlitSurface(optimizedSurface, NULL, destSurface, &rectPos);
}

void Creature::updatePos() {
    rectPos.x = posX;
    rectPos.y = posY;
}
