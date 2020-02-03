#include <stdio.h>
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <boost/config/compiler/gcc.hpp>

#include "Creature.h"

Creature::Creature(SDL_Surface *surfaceptr) {
	surface = surfaceptr;
}

Creature::~Creature() {
}

void Creature::draw(SDL_Renderer *renderer, Settings *settings) {
	if (BOOST_UNLIKELY(drawable_->texture == nullptr)) {

		drawable_->texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_QueryTexture(drawable_->texture, nullptr, nullptr,
				&drawable_->rect_pos.w, &drawable_->rect_pos.h);
		SDL_SetTextureAlphaMod(drawable_->texture, alpha);
	}
	if (BOOST_LIKELY(settings->draw_textures)) {
		if (BOOST_UNLIKELY(isActive)) {
			SDL_RenderDrawRect(renderer, &drawable_->rect_pos);
		}
		SDL_RenderCopyEx(renderer, drawable_->texture, nullptr,
				&drawable_->rect_pos, -drawable_->rot_angle, nullptr,
				SDL_FLIP_NONE);
	}
	if (BOOST_LIKELY(settings->draw_vectors)) {
		drawable_->vect.draw(renderer);
	}
}

void Creature::update(const uint32_t *timeDelta, Settings *settings) {
	if (BOOST_LIKELY(settings->rotate)) {
		rotate(rotation_speed * *timeDelta);
		if (BOOST_LIKELY(settings->move)) {
			move(timeDelta);
		}
	}
}

void Creature::rotate(const float &rotationAngle) {
	drawable_->rot_angle += rotationAngle;
	if (BOOST_UNLIKELY(std::abs(drawable_->rot_angle) > f360)) {
		drawable_->rot_angle = fmod(drawable_->rot_angle, f360);
	}
	drawable_->vect.setAngle(&drawable_->rot_angle);
//  drawable_->vect.add(&drawable_->rot_angle);
	drawable_->rect_pos.x = pos_x; // - rotated_Surface->w / 2 - optimized_surface->w / 2;
	drawable_->rect_pos.y = pos_y; // - rotated_Surface->h / 2 - optimized_surface->h / 2;
}

void Creature::move(const uint32_t *time_delta) {
	pos_x += sin(drawable_->rot_angle * M_PI / f180) * speed * *time_delta;
	pos_y += cos(drawable_->rot_angle * M_PI / f180) * speed * *time_delta;
	drawable_->vect.setPos(&pos_x, &pos_y);
}

void Creature::setSpeed(float &speed) {
	this->speed = speed;
}
void Creature::setRotationSpeed(float &speed) {
	this->rotation_speed = speed;
}
void Creature::setAlpha(int alpha) {
	std::cout<<"Alpha:" << alpha<<std::endl;
	this->alpha = alpha;
}
void Creature::setActive() {
	if (!isActive) {
		SDL_SetTextureAlphaMod(drawable_->texture, 255);
	isActive = true;
	}
}
void Creature::setInActive() {
	if (isActive) {
		SDL_SetTextureAlphaMod(drawable_->texture, alpha);
	isActive = false;
	}
}


std::string Creature::getInfo() {
	return "speed: " + std::to_string(speed) + ", rotation_val: ";
}
