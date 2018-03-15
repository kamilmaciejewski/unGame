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
        if( surface == NULL )
        {
            printf( "Unable to load image");
        }
        else {printf("OK");}
    rotAngle = 0;
    posX = 100;
    posY = 100;


}

Player::~Player() {
}

void Player::draw(SDL_Surface* destSurface){
    updatePos();
    SDL_BlitSurface(surface, NULL, destSurface, &rectPos);
}

void Player::updatePos(){
    rectPos.x = posX;
    rectPos.y = posY;
}
