/*
 * BasicObject.h
 *
 *  Created on: 22 mar 2018
 *      Author: Kamil
 */

#ifndef UNGAME_BASICOBJECT_H_
#define UNGAME_BASICOBJECT_H_

#include <SDL2/SDL.h>
//#include <SDLEngine.h>

class BasicObject {

protected:

  SDL_Surface* surface = nullptr;
  SDL_Surface* optimized_surface = nullptr;
  SDL_Surface* rotated_Surface = nullptr;
  SDL_Texture* texture = nullptr;
  SDL_Rect rect_pos {0, 0, 0, 0 };
  float pos_x = 0, pos_y = 0;
  bool isObjectOnScreen(int&, int&);
public:

  BasicObject();
  virtual ~BasicObject();
  void setPos(int, int);
};

#endif /* UNGAME_BASICOBJECT_H_ */
