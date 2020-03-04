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
			for (auto vect : *multiview) {
				vect->draw(renderer);
			}
			SDL_RenderDrawRect(renderer, &drawable_->rect_draw);
		}
		SDL_RenderCopyEx(renderer, drawable_->texture, nullptr,
				&drawable_->rect_draw, -drawable_->rot_angle, nullptr,
				SDL_FLIP_NONE);
	}
	if (BOOST_LIKELY(settings->draw_vectors)) {
//		drawable_->vect.draw(renderer); //draw direction vector
		//FOV presentation
//		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_TRANSPARENT);
//			for (int dx = -20; dx < 20; dx++) {
//				double dxrad = degToRad(dx);
//
//				for (int x = 0; x < 100; x++) {
//					SDL_RenderDrawPoint(renderer,
//							pos.x + (x * sin(drawable_->vect->getAngleRad() + dxrad)),
//							pos.y + (x * cos(drawable_->vect->getAngleRad() + dxrad)));
//				}
//			}

	}
}

void Creature::update(const uint32_t *timeDelta, Settings *settings) {
	if (BOOST_LIKELY(settings->rotate)) {
		rotate(rotation_speed * *timeDelta);
		if (BOOST_LIKELY(settings->move)) {
			move(timeDelta);
			if (pos.x < 0) {
				pos.x = settings->SCREEN_WIDTH + pos.x;
			} else if (pos.x > settings->SCREEN_WIDTH) {
				pos.x = pos.x - settings->SCREEN_WIDTH;
			}
			if (pos.y < 0) {
				pos.y = settings->SCREEN_HEIGHT + pos.y;
			} else if (pos.y > settings->SCREEN_HEIGHT) {
				pos.y = pos.y - settings->SCREEN_HEIGHT;
			}
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
void Creature::setInactive() {
	if (activeState) {
		SDL_SetTextureAlphaMod(drawable_->texture, alpha);
		activeState = false;
	}
}

bool Creature::isActive() {
	return activeState;
}

bool Creature::lookAt(const Creature *otherCreature) {
	auto vect = lookAt(otherCreature->pos);
	if (vect != nullptr) {
		multiview->push_back(vect);
		return true;
	}
	return false;
}
UNG_Vector* Creature::lookAt(const SDL_FPoint point) {
	float dist = distance(pos, point);
	if (dist != 0 && abs(dist) < view_dist) {
		float angle = radToDeg(atan2(point.x - pos.x, point.y - pos.y));
		if (getDifference(vect->getAngleDeg(), angle) < fov) {
			return new UNG_Vector(&pos, angle, dist);
		}
	}
	return nullptr;
}

std::string Creature::getInfo() {
	return "x: " + std::to_string(pos.x) + "y: " + std::to_string(pos.y);
}
