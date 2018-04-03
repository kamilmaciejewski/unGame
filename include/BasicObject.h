#ifndef UNGAME_BASICOBJECT_H_
#define UNGAME_BASICOBJECT_H_

#include <SDL2/SDL.h>

class BasicObject {

protected:

  SDL_Surface* surface = nullptr;
  SDL_Surface* optimized_surface = nullptr;
  SDL_Surface* rotated_Surface = nullptr;
  SDL_Texture* texture = nullptr;
  SDL_Rect rect_pos {0, 0, 0, 0 };
  float pos_x = 0, pos_y = 0;
  bool isObjectOnScreen(const int*, const int*) const;
public:

  BasicObject();
  virtual ~BasicObject();
  void setPos(const int&, const int&) ;
};

#endif /* UNGAME_BASICOBJECT_H_ */
