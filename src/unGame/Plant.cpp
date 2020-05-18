#include <stdio.h>
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <boost/config/compiler/gcc.hpp>

#include <UNGPlant.h>

Plant::Plant() {
	drawable_->rect_draw.h = 50;
	drawable_->rect_draw.w = 50;
}

Plant::~Plant() {
}

void Plant::draw(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0x0, 0xF0, 0x0, SDL_ALPHA_TRANSPARENT);
	SDL_RenderDrawRect(renderer, &drawable_->rect_draw);
 	}

void Plant::update() {
	drawable_->rect_draw.x = pos.x - (drawable_->rect_draw.w / 2); // - rotated_Surface->w / 2 - optimized_surface->w / 2;
	drawable_->rect_draw.y = pos.y - (drawable_->rect_draw.h / 2); // - rotated_Surface->h / 2 - optimized_surface->h / 2;
}


void Plant::setActive() {
	if (!activeState) {
		activeState = true;
	}
}
void Plant::setInactive() {
	if (activeState) {
		activeState = false;
	}
}

bool Plant::isActive() {
	return activeState;
}

std::string Plant::getInfo() {
	return "Plant";
}
