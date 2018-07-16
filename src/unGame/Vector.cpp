/*
 * Vector.cpp
 *
 *  Created on: 16 lip 2018
 *      Author: ekammac
 */

#include "Vector.h"

Vector::Vector() {
  value = 0;
  angle = 0;
  posX = 0;
  posY = 0;

}

void Vector::draw(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderDrawLine(renderer, posX, posY, posX + 10, posY + 10);
}

void Vector::setPos(const float* posX_, const float* posY_){
  posX = *posX_;
  posY = *posY_;
}
