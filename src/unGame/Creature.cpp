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
				&drawable_->rect_draw.w, &drawable_->rect_draw.h);
		SDL_SetTextureAlphaMod(drawable_->texture, alpha);
	}
	if (BOOST_LIKELY(settings->draw_textures)) {
		if (BOOST_UNLIKELY(activeState)) {
			SDL_RenderDrawRect(renderer, &drawable_->rect_draw);
		}
		SDL_RenderCopyEx(renderer, drawable_->texture, nullptr,
				&drawable_->rect_draw, -drawable_->rot_angle, nullptr,
				SDL_FLIP_NONE);
	}
	if (BOOST_LIKELY(settings->draw_vectors)) {
		drawable_->vect.draw(renderer);
		if (abs(drawable_->vect.angleDeg-drawable_->view_vect.angleDeg) < 90){
		drawable_->view_vect.draw(renderer);
		}

	}
}

void Creature::update(const uint32_t *timeDelta, Settings *settings) {
	if (BOOST_LIKELY(settings->rotate)) {
		rotate(rotation_speed * *timeDelta);
		if (BOOST_LIKELY(settings->move)) {
			move(timeDelta);
		}
		drawable_->pos.x = pos_x; // - rotated_Surface->w / 2 - optimized_surface->w / 2;
		drawable_->pos.y = pos_y; // - rotated_Surface->h / 2 - optimized_surface->h / 2;
		drawable_->rect_draw.x = pos_x-(drawable_->rect_draw.w/2); // - rotated_Surface->w / 2 - optimized_surface->w / 2;
		drawable_->rect_draw.y = pos_y-(drawable_->rect_draw.h/2); // - rotated_Surface->h / 2 - optimized_surface->h / 2;

	}
}

void Creature::rotate(const float &rotationAngle) {
	drawable_->rot_angle += rotationAngle;
	if (BOOST_UNLIKELY(std::abs(drawable_->rot_angle) > f360)) {
		drawable_->rot_angle = fmod(drawable_->rot_angle, f360);
	}
	drawable_->vect.setAngle(&drawable_->rot_angle);
}

void Creature::move(const uint32_t *time_delta) {
	pos_x += sin(drawable_->rot_angle * M_PI / f180) * speed * *time_delta;
	pos_y += cos(drawable_->rot_angle * M_PI / f180) * speed * *time_delta;
	drawable_->vect.setPos(&pos_x, &pos_y);
	drawable_->view_vect.setPos(&pos_x, &pos_y);

}

void Creature::setSpeed(float &speed) {
	this->speed = speed;
}
void Creature::setRotationSpeed(float &speed) {
	this->rotation_speed = speed;
}
void Creature::setAlpha(int alpha) {
	this->alpha = alpha;
}
void Creature::setActive() {
	if (!activeState) {
		SDL_SetTextureAlphaMod(drawable_->texture, 255);
		activeState = true;
	}
}
void Creature::setInActive() {
	if (activeState) {
		SDL_SetTextureAlphaMod(drawable_->texture, alpha);
		activeState = false;
	}
}

bool Creature::isActive() {
	return activeState;
}

void Creature::lookAt(const SDL_Point &point) {
	double dist = sqrt(
			(pow(drawable_->pos.x - point.x, 2)
					+ pow(drawable_->pos.y - point.y, 2)));
	if (dist !=0
			&& abs(dist) < 100
			){
		double angle = atan2(point.x - pos_x, point.y - pos_y) * 180 / M_PI;
		drawable_->view_vect.setAngle(&angle);
	}
}



std::string Creature::getInfo() {
	return "angle: " + std::to_string(drawable_->vect.angleDeg) + "view angle:" + std::to_string(drawable_->view_vect.angleDeg);
}
