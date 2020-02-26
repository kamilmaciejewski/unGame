/*
 * Vector.cpp
 *
 *  Created on: 16 lip 2018
 *      Author: ekammac
 */

#include "Vector.h"
#include <iostream>

UNG_Vector::UNG_Vector(SDL_FPoint *pos_) {
	value = 40;
	angle = 0.0;
	pos = pos_;

}
UNG_Vector::UNG_Vector(SDL_FPoint *pos_, float _angle , float _value) {
	value = _value;
	angle = _angle;
	pos = pos_;

}


void UNG_Vector::draw(SDL_Renderer *renderer) {
//	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawLine(renderer, pos->x, pos->y,
			pos->x + (value * sin(degToRad(angle))),
			pos->y + (value * cos(degToRad(angle))));
}

void UNG_Vector::setVal(float &val) {
	value = val;
}

void UNG_Vector::setAngleDeg(float &angle_) {
	angle = angle_;
}
void UNG_Vector::setAngleRad(float &angle_) {
	angle = radToDeg(angle_);
}

void UNG_Vector::add(UNG_Vector *vector) {
	this->value = (this->value + vector->angle)
			* cos(this->angle + vector->angle);
	this->angle = (this->angle + vector->angle) / 2;
}

//TODO: FIX
void UNG_Vector::add(float *angle) {
	this->angle += cos(this->angle + *angle);
}

float UNG_Vector::getAngleDeg() {
	return angle;
}

float UNG_Vector::getAngleRad() {
	return degToRad(angle);
}
