/*
 * BasicObject.cpp
 *
 *  Created on: 22 mar 2018
 *      Author: Kamil
 */

#include "BasicObject.h"
#include "SDLEngine.h"

BasicObject::BasicObject() {
  // TODO Auto-generated constructor stub

}

BasicObject::~BasicObject() {
  // TODO Auto-generated destructor stub
}

bool BasicObject::isObjectOnScreen(int& screenWidth, int& screenHeight) {
  return (rect_pos.x >= (-rect_pos.w) && rect_pos.y >= (-rect_pos.h)
      && rect_pos.x <= (screenWidth + rect_pos.w)
      && rect_pos.y <= (screenHeight + rect_pos.h));
}

void BasicObject::setPos(int pos_x, int pos_y) {
  this->pos_x = pos_x;
  this->pos_y = pos_y;
  rect_pos.x = pos_x;
  rect_pos.y = pos_y;
}



