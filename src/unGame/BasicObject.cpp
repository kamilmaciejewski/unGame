#include "BasicObject.h"
#include "SDLEngine.h"

BasicObject::BasicObject() {
  drawable_data.texture = nullptr;
  drawable_data.rect_pos= {0, 0, 0, 0 };
}

BasicObject::~BasicObject() {
}

bool BasicObject::isObjectOnScreen(const int* screenWidth, const int* screenHeight) const {
  return (drawable_->rect_pos.x >= (-drawable_->rect_pos.w) && drawable_->rect_pos.y >= (-drawable_->rect_pos.h)
      && drawable_->rect_pos.x <= (*screenWidth + drawable_->rect_pos.w)
      && drawable_->rect_pos.y <= (*screenHeight + drawable_->rect_pos.h));
}

void BasicObject::setPos(const int& pos_x, const int& pos_y) {
  this->pos_x = pos_x;
  this->pos_y = pos_y;
  drawable_->rect_pos.x = pos_x;
  drawable_->rect_pos.y = pos_y;
}

drawable* BasicObject::getDrawable(){
  return (drawable_);
}



