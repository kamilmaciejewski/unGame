#include <Object.h>
#include "SDLEngine.h"

Object::Object() {
	drawable_data.texture = nullptr;
}

Object::~Object() {
}

bool Object::isObjectOnScreen(const int *screenWidth,
		const int *screenHeight) const {
//  return (drawable_->pos->x >= (-drawable_->rect_draw.w)
//      && drawable_->pos->y >= (-drawable_->rect_draw.h)
//      && drawable_->pos->x <= (*screenWidth + drawable_->rect_draw.w)
//      && drawable_->pos->y <= (*screenHeight + drawable_->rect_draw.h));
	return true; //fixme
}

void Object::setPos(const SDL_FPoint &pos_) {
	this->pos = pos_;
//  drawable_->pos = &pos;
}

drawable* Object::getDrawable() {
	return (drawable_);
}

