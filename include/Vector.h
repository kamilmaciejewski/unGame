#ifndef UNGAME_VECTOR_H_
#define UNGAME_VECTOR_H_

#include <SDL2/SDL.h>
class Vector {
public:
  Vector();
  virtual ~Vector() = default;
  void draw(SDL_Renderer*);
  void setPos(const float*, const float*);
  float posX, posY, value, angle;
};


#endif /* UNGAME_VECTOR_H_ */
