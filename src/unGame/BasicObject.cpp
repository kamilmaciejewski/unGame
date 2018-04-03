#include "BasicObject.h"
#include "SDLEngine.h"

BasicObject::BasicObject() {
}

BasicObject::~BasicObject() {
}

bool BasicObject::isObjectOnScreen(const int* screenWidth, const int* screenHeight) const {
  return (rect_pos.x >= (-rect_pos.w) && rect_pos.y >= (-rect_pos.h)
      && rect_pos.x <= (*screenWidth + rect_pos.w)
      && rect_pos.y <= (*screenHeight + rect_pos.h));
}

void BasicObject::setPos(const int& pos_x, const int& pos_y) {
  this->pos_x = pos_x;
  this->pos_y = pos_y;
  rect_pos.x = pos_x;
  rect_pos.y = pos_y;
}



