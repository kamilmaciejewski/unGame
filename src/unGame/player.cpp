/*
 * player.cpp
 *
 *  Created on: 9 mar 2018
 *      Author: Kamil
 */

#include "player.h"
#include <SDL2/SDL.h>

player::player() {
    skin = "res/defultSkin.bmp";
    rotAngle = 0;
    posX = 0;
    posY = 0;

}

player::~player() {
}

