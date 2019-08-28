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
  angleDeg = 0;
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

void Vector::setAngle(float * angle_) {
  angleDeg = *angle_;
  angleRad = angleDeg * M_PI / 180;
}

void Vector::add(Vector* vector){
this->value = (this->value+ vector->angleRad) * cos(this->angleRad + vector->angleRad);
this->angleRad =  (this->angleRad + vector->angleRad) /2;
}

//TODO: FIX
void Vector::add(float* angle){
this->angleRad += cos(this->angleRad + *angle);
}

