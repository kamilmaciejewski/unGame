#include <stdio.h>
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <boost/config/compiler/gcc.hpp>

#include <UNGPlant.h>

Plant::Plant(SDL_FPoint pos) {
	this->pos = pos;

	drawable->rect_draw.h = 50;
	drawable->rect_draw.w = 50;
	drawable->rect_draw = SDL_Rect {
			(int) (pos.x - (drawable->rect_draw.w / 2)), (int) (pos.y
					- (drawable->rect_draw.w / 2)), size, size };
}

Plant::~Plant() {
}

void Plant::draw(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 0x0, 0xF0, 0x0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &drawable->rect_draw);
	stringColor(renderer, pos.x - 25, pos.y + 25,
			("en:" + std::to_string(energy)).c_str(), UNG_Globals::GREEN);
}

void Plant::update() {

//	drawable->rect_draw.h = energy/5;
//	drawable->rect_draw.w = energy/5;

	if (energy < 1) {
		pos.x = (float) (rand() % (UNG_Globals::worldBox.w - 100)) + 50;
		pos.y = (float) (rand() % (UNG_Globals::worldBox.h - 100)) + 50;
		drawable->rect_draw = SDL_Rect { (int) (pos.x
				- (drawable->rect_draw.w / 2)), (int) (pos.y
				- (drawable->rect_draw.w / 2)), size,size };
		energy = 100;
	}
}

bool Plant::isAlive() {
	return energy>1;
}

std::string Plant::getInfo() {
	return "Plant";
}

