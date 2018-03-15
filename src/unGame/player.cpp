/*
 * player.cpp
 *
 *  Created on: 9 mar 2018
 *      Author: Kamil
 */

#include "Player.h"
#include <SDL2/SDL.h>

Player::Player() {
    surface = SDL_LoadBMP("res/arrow.bmp");
    optimizedSurface = SDL_ConvertSurface( surface, surface->format, 0 );
    SDL_FreeSurface(surface);

        if( surface == NULL )
        {
            printf( "Unable to load image: %s\n", SDL_GetError());
        }
    rotAngle = 0;
    posX = 100;
    posY = 100;


}

Player::~Player() {
}

void Player::draw(SDL_Surface* destSurface){
    updatePos();
    SDL_BlitSurface(optimizedSurface, NULL, destSurface, &rectPos);
}

void Player::updatePos(){
    rectPos.x = posX;
    rectPos.y = posY;
}
