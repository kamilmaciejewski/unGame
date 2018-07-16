#ifndef UNGAME_BASICOBJECT_H_
#define UNGAME_BASICOBJECT_H_

#include <SDL2/SDL.h>

class BasicObject {

protected:

  SDL_Surface* surface = nullptr;
  SDL_Texture* texture = nullptr;
  float pos_x = 0, pos_y = 0;
  bool isObjectOnScreen(const int*, const int*) const;
public:
//TODO: function getPos
  SDL_Rect rect_pos {0, 0, 0, 0 };
  BasicObject();
  virtual ~BasicObject();
  void setPos(const int&, const int&) ;
};

#endif /* UNGAME_BASICOBJECT_H_ */
