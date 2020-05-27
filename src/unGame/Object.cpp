#include "UNGObject.h"
#include "SDLEngine.h"

Object::Object() {
	drawable->texture = nullptr;
}

Object::~Object() {
	SDL_DestroyTexture(drawable->texture);
	delete drawable;
	drawable = nullptr;
	delete vect;
	vect = nullptr;
}

bool Object::isObjectOnScreen(const int *screenWidth,
		const int *screenHeight) const {
//  return (drawable->pos->x >= (-drawable->rect_draw.w)
//      && drawable->pos->y >= (-drawable->rect_draw.h)
//      && drawable->pos->x <= (*screenWidth + drawable->rect_draw.w)
//      && drawable->pos->y <= (*screenHeight + drawable->rect_draw.h));
	return true; //fixme
}

void Object::setPos(const SDL_FPoint &pos_) {
	this->pos = pos_;
//  drawable->pos = &pos;
}

Drawable* Object::getDrawable() {
	return (drawable);
}

