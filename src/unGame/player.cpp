/*
 * player.cpp
 *
 *  Created on: 9 mar 2018
 *      Author: Kamil
 */

#include "Player.h"
#include <SDL2/SDL.h>

Player::Player() {
    skin = "res/defultSkin.bmp";
    rotAngle = 0;
    posX = 0;
    posY = 0;

}

Player::~Player() {
}

