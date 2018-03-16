/*
 * Creature.cpp
 *
 *  Created on: 9 mar 2018
 *      Author: Kamil
 */

#include "Creature.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <cmath>

#include "../rotozoom/SDL2_rotozoom.h"


Creature::Creature() {
    surface = SDL_LoadBMP("res/arrow.bmp");
    SDL_SetColorKey(surface,SDL_TRUE ,SDL_MapRGB(surface->format,0xff,0x0,0xff));
    optimizedSurface = SDL_ConvertSurface(surface, surface->format, 0);
    SDL_FreeSurface(surface);

    if (surface == NULL) {
        printf("Unable to load image: %s\n", SDL_GetError());
    }
    setRotationAngle(0);
    posX=0;
    posY=0;
}

Creature::~Creature() {
}

void Creature::draw(SDL_Surface* destSurface) {
    setRotationAngle(rotAngle + (rotationSpeed * 0.1));
    SDL_BlitSurface(rotSurface, NULL, destSurface, &rectPos);
}

void Creature::setPos(int newPosX, int newPosY) {
    posX = newPosX;
    posY = newPosY;
    rectPos.x = posX;
    rectPos.y = posY;
}

void Creature::setRotationAngle(float rotationAngle){
    if(rotationAngle>360) {rotationAngle-=360;}
    if(rotationAngle<-360) {rotationAngle+=360;}

    rotAngle = rotationAngle;
    SDL_FreeSurface(rotSurface);
    rotSurface = rotozoomSurface(optimizedSurface, rotAngle, 1, 0);
    float x = sin(rotationAngle * M_PI / 180) * speed * 0.1;
    float y = cos(rotationAngle * M_PI / 180) * speed * 0.1;
    posX += x;
    posY += y;
    rectPos.x =posX - rotSurface->w / 2 - optimizedSurface->w / 2;
    rectPos.y = posY  - rotSurface->h / 2 - optimizedSurface->h / 2;
}

void Creature::setSpeed(float speed) {
        this->speed = speed;
    }
void Creature::setRotationSpeed(float speed) {
        this->rotationSpeed = speed;
    }
