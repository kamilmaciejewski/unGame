#include <stdio.h>
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <boost/config/compiler/gcc.hpp>

#include <UNGPlant.h>

Plant::Plant(SDL_FPoint pos) {
	this->pos = pos;

	rect_food = SDL_Rect { (int) (pos.x
			- ((int) (sqrt(energy)*sizeFactor) / 2)), (int) (pos.y
			- ((int) (sqrt(energy)*sizeFactor) / 2)), (int) sqrt(energy)*sizeFactor,
			(int) sqrt(energy)*sizeFactor };
}

Plant::~Plant() {
}

void Plant::draw(SDL_Renderer *renderer) {
	drawable->rect_draw = rect_food;
	SDL_SetRenderDrawColor(renderer, 0x0, 0xF0, 0x0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &rect_food);
	stringColor(renderer, pos.x - 25, pos.y + 25,
			("en:" + std::to_string(energy)).c_str(), UNG_Globals::GREEN);
}

void Plant::update() {

//	drawable->rect_draw.h = energy/5;
//	drawable->rect_draw.w = energy/5;
	rect_food = SDL_Rect {
			(int) (pos.x - (rect_food.w / 2)), (int) (pos.y
					- (rect_food.w / 2)), (int) sqrt(energy)*sizeFactor,
			(int) sqrt(energy)*sizeFactor };

	if (energy < startEnergy / 10) {
		pos.x = (float) (rand() % (UNG_Globals::worldBox.w - 100)) + 50;
		pos.y = (float) (rand() % (UNG_Globals::worldBox.h - 100)) + 50;
		rect_food.x = pos.x - ((int) (sqrt(energy)*sizeFactor) / 2);
		rect_food.y = pos.y - ((int) (sqrt(energy)*sizeFactor) / 2);
//		rect_food = SDL_Rect { (int) (pos.x
//				- (rect_food.w / 2)), (int) (pos.y
//				- (rect_food.w / 2)), size,size };
		energy = startEnergy;
	}
}

bool Plant::isAlive() {
	return energy > 1;
}

std::string Plant::getInfo() {
	return "Plant";
}

