#include <stdio.h>
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <boost/config/compiler/gcc.hpp>
#include <UNGGlobals.h>

#include "Creature.h"

Creature::Creature(SDL_Surface *surfaceptr) {
	multiview = new std::vector<UNG_Vector*>();
	multiview->reserve(MAX_VIEW_ENTRIES);
	surface = surfaceptr;
}

Creature::~Creature() {
	cleanupView();
	delete multiview;
}

void Creature::draw(SDL_Renderer *renderer, Settings *settings) {
	if (!isAlive()) {
		return;
	}
	if (BOOST_UNLIKELY(drawable_->texture == nullptr)) {
		drawable_->texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_QueryTexture(drawable_->texture, nullptr, nullptr,
				&drawable_->rect_draw.w, &drawable_->rect_draw.h);
	}
	if (BOOST_LIKELY(settings->draw_textures)) {
		SDL_SetTextureAlphaMod(drawable_->texture, energy);
		if (BOOST_UNLIKELY(activeState)) {
			for (auto vect : *multiview) {
				vect->draw(renderer);
			}
			SDL_RenderDrawRect(renderer, &drawable_->rect_draw);
		}

		SDL_RenderCopyEx(renderer, drawable_->texture, nullptr,
				&drawable_->rect_draw, -drawable_->rot_angle, nullptr,
				SDL_FLIP_NONE);
	}
//	if (BOOST_LIKELY(settings->draw_vectors)) {
//		drawable_->vect.draw(renderer); //draw direction vector
}

void Creature::update(const uint32_t *timeDelta, Settings *settings) {
	if (!isAlive()) {
		return;
	}
	if (BOOST_LIKELY(settings->rotate)) {
		rotate(rotation_speed * *timeDelta);
		if (BOOST_LIKELY(settings->move)) {
			move(timeDelta);
		}
		drawable_->rect_draw.x = pos.x - (drawable_->rect_draw.w / 2); // - rotated_Surface->w / 2 - optimized_surface->w / 2;
		drawable_->rect_draw.y = pos.y - (drawable_->rect_draw.h / 2); // - rotated_Surface->h / 2 - optimized_surface->h / 2;
	}
}

void Creature::rotate(const float &rotationAngle) {
	drawable_->rot_angle += rotationAngle;
	if (BOOST_UNLIKELY(std::abs(drawable_->rot_angle) > f360)) {
		drawable_->rot_angle = fmod(drawable_->rot_angle, f360);
	}
	vect->setAngleDeg(drawable_->rot_angle);
}

void Creature::move(const uint32_t *time_delta) {
	pos.x += sin(degToRad(drawable_->rot_angle)) * speed * *time_delta;
	pos.y += cos(degToRad(drawable_->rot_angle)) * speed * *time_delta;
	energy -= metabolism_factor * (speed * *time_delta);
}

void Creature::setSpeed(float &speed) {
	this->speed = speed;
}

void Creature::setRotationSpeed(float &speed) {
	this->rotation_speed = speed;
}

void Creature::setActive() {
	if (!activeState) {
		SDL_SetTextureAlphaMod(drawable_->texture, 255);
		activeState = true;
	}
}

void Creature::setInactive() {
	if (activeState) {
		SDL_SetTextureAlphaMod(drawable_->texture, energy);
		activeState = false;
	}
}

bool Creature::isActive() {
	return activeState;
}

bool Creature::isAlive() {
	return energy > 0;

}

void Creature::cleanupView() {
	if (multiview->size() > 0) {

		for (auto vect : *multiview) {
			delete vect;
		}
		multiview->clear();
	}
}

bool Creature::lookAt(const Creature *otherCreature) {
	if (multiview->size() < MAX_VIEW_ENTRIES) {
		auto vect = lookAt(otherCreature->pos);
		if (vect != nullptr) {
			multiview->push_back(vect);
			return true;
		}
	}
	return false;
}

bool Creature::lookAt(const Plant *plant) {
	if (multiview->size() < MAX_VIEW_ENTRIES) {
		auto vect = lookAt(plant->pos);
		if (vect != nullptr) {
			multiview->push_back(vect);
			return true;
		}
	}
	return false;
}

UNG_Vector* Creature::lookAt(const SDL_FPoint point) {
	float dist = distance(pos, point);
	if (dist != 0 && abs(dist) < VIEW_DIST) {
		float angle = radToDeg(atan2(point.x - pos.x, point.y - pos.y));
		if (getDifference(vect->getAngleDeg(), angle) < FOV) {
			return new UNG_Vector(&pos, angle, dist);
		}
	}
	return nullptr;
}

std::string Creature::getInfo() {
	return "energy: " + std::to_string(energy) + ", view: "
			+ std::to_string(multiview->size());
}
