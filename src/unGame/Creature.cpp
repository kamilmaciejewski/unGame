#include <stdio.h>
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <boost/config/compiler/gcc.hpp>

#include "Creature.h"
#include "Globals.h"

Creature::Creature(SDL_Surface *surfaceptr) {
	multiview = new std::vector<UNG_Vector*>();
	multiview->reserve(max_view_entries);
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
//			wrapScreenPos();
		}
		drawable_->rect_draw.x = pos.x - (drawable_->rect_draw.w / 2); // - rotated_Surface->w / 2 - optimized_surface->w / 2;
		drawable_->rect_draw.y = pos.y - (drawable_->rect_draw.h / 2); // - rotated_Surface->h / 2 - optimized_surface->h / 2;
	}
}
//void Creature::wrapScreenPos() {
//	if (pos.x < 0) {
//		pos.x = UNG_Globals::SCREEN_W + pos.x;
//	} else if (pos.x > UNG_Globals::SCREEN_W) {
//		pos.x = pos.x - UNG_Globals::SCREEN_W;
//	}
//	if (pos.y < 0) {
//		pos.y = UNG_Globals::SCREEN_H + pos.y;
//	} else if (pos.y > UNG_Globals::SCREEN_H) {
//		pos.y = pos.y - UNG_Globals::SCREEN_H;
//	}
//}

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
//void Creature::setAlpha(int alpha) {
//	this->alpha = alpha;
//}
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
	if (multiview->size() < max_view_entries) {
		auto vect = lookAt(otherCreature->pos);
		if (vect != nullptr) {
			multiview->push_back(vect);
			return true;
		}
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
	return "energy: " + std::to_string(energy) + ", view: "
			+ std::to_string(multiview->size());
}
