#include <stdio.h>
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <boost/config/compiler/gcc.hpp>

#include "Plant.h"

Plant::Plant(SDL_Surface *surfaceptr) {
	surface = surfaceptr;
}

Plant::~Plant() {
}

void Plant::draw(SDL_Renderer *renderer, Settings *settings) {
	if (BOOST_UNLIKELY(drawable_->texture == nullptr)) {
		drawable_->texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_QueryTexture(drawable_->texture, nullptr, nullptr,
				&drawable_->rect_draw.w, &drawable_->rect_draw.h);
//		SDL_SetTextureAlphaMod(drawable_->texture, alpha);
	}
	if (BOOST_LIKELY(settings->draw_textures)) {
//		if (BOOST_UNLIKELY(activeState)) {
//			for (auto vect : *multiview) {
//				vect->draw(renderer);
//			}
//			SDL_RenderDrawRect(renderer, &drawable_->rect_draw);
//		}
		SDL_RenderCopy(renderer, drawable_->texture, &drawable_->rect_draw,
				nullptr);
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

void Plant::update(const uint32_t *timeDelta, Settings *settings) {
//	if (BOOST_LIKELY(settings->rotate)) {
//		rotate(rotation_speed * *timeDelta);
//		if (BOOST_LIKELY(settings->move)) {
//			move(timeDelta);
//		}
//		drawable_->rect_draw.x = pos.x - (drawable_->rect_draw.w / 2); // - rotated_Surface->w / 2 - optimized_surface->w / 2;
//		drawable_->rect_draw.y = pos.y - (drawable_->rect_draw.h / 2); // - rotated_Surface->h / 2 - optimized_surface->h / 2;
//	}
}

//void Plant::rotate(const float &rotationAngle) {
//	drawable_->rot_angle += rotationAngle;
//	if (BOOST_UNLIKELY(std::abs(drawable_->rot_angle) > f360)) {
//		drawable_->rot_angle = fmod(drawable_->rot_angle, f360);
//	}
//	vect->setAngleDeg(drawable_->rot_angle);
//}
//
//void Plant::move(const uint32_t *time_delta) {
//	pos.x += sin(degToRad(drawable_->rot_angle)) * speed * *time_delta;
//	pos.y += cos(degToRad(drawable_->rot_angle)) * speed * *time_delta;
//
//}

//void Plant::setSpeed(float &speed) {
//	this->speed = speed;
//}
//void Plant::setRotationSpeed(float &speed) {
//	this->rotation_speed = speed;
//}
//void Plant::setAlpha(int alpha) {
//	this->alpha = alpha;
//}

void Plant::setActive() {
	if (!activeState) {
//		SDL_SetTextureAlphaMod(drawable_->texture, 255);
		activeState = true;
	}
}
void Plant::setInactive() {
	if (activeState) {
//		SDL_SetTextureAlphaMod(drawable_->texture, alpha);
		activeState = false;
	}
}

bool Plant::isActive() {
	return activeState;
}

//bool Plant::lookAt(const Plant* otherPlant) {
//	auto vect = lookAt(otherPlant->pos);
//	if (vect !=nullptr) {
//		multiview->push_back(vect);
//		return true;
//	}
//	return false;
//}
//UNG_Vector* Plant::lookAt(const SDL_FPoint point) {
//	float dist = distance(pos, point);
//	if (dist != 0 && abs(dist) < view_dist) {
//		float angle = radToDeg(atan2(point.x - pos.x, point.y - pos.y));
//		if (getDifference(vect->getAngleDeg(), angle) < fov) {
//			return new UNG_Vector(&pos, angle, dist);
//		}
//	}
//	return nullptr;
//}

std::string Plant::getInfo() {
	return "Plant";
}
