/*
 * Vector.cpp
 *
 *  Created on: 16 lip 2018
 *      Author: ekammac
 */

#include "Vector.h"
#include <iostream>

Vector::Vector() {
  value = 40;
  angleDeg = 270;
  angleRad = angleDeg * M_PI / 180;
  posX = 0;
  posY = 0;

}

void Vector::draw(SDL_Renderer* renderer) {
  SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  SDL_RenderDrawLine(renderer, posX, posY, posX + (value * sin(angleRad)),
      posY + (value * cos(angleRad)));
}

void Vector::setPos(const float* posX_, const float* posY_) {
  posX = *posX_;
  posY = *posY_;
}

void Vector::setAngle(const int * angle_) {
  angleDeg = *angle_;
  angleRad = angleDeg * M_PI / 180;
}
