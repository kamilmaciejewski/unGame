#include <Object.h>
#include "SDLEngine.h"

Object::Object() {
  drawable_data.texture = nullptr;
  drawable_data.pos= {0,0};
}

Object::~Object() {
}

bool Object::isObjectOnScreen(const int* screenWidth,
    const int* screenHeight) const {
  return (drawable_->pos.x >= (-drawable_->rect_draw.w)
      && drawable_->pos.y >= (-drawable_->rect_draw.h)
      && drawable_->pos.x <= (*screenWidth + drawable_->rect_draw.w)
      && drawable_->pos.y <= (*screenHeight + drawable_->rect_draw.h));
}

void Object::setPos(const int& pos_x, const int& pos_y) {
  this->pos_x = pos_x;
  this->pos_y = pos_y;
  drawable_->pos.x = pos_x;
  drawable_->pos.y = pos_y;
}

drawable* Object::getDrawable() {
  return (drawable_);
}

