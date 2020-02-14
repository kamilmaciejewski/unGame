#ifndef UNGAME_BASICOBJECT_H_
#define UNGAME_BASICOBJECT_H_

#include <SDL2/SDL.h>
#include "Vector.h"
#include "Settings.h"
#include "Drawable.h"

class Object {

protected:

  drawable drawable_data;
  drawable* drawable_ = &drawable_data;
  SDL_Surface* surface = nullptr;

//  SDL_Point pos_{0,0};
  float pos_x = 0, pos_y = 0;
  bool isObjectOnScreen(const int*, const int*) const;
public:
//TODO: function getPos
  Object();
  virtual ~Object();
  void setPos(const int&, const int&);
//void setPos(const SDL_Point&);
  drawable* getDrawable();
};

#endif /* UNGAME_BASICOBJECT_H_ */
