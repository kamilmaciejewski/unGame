#ifndef UNGAME_VECTOR_H_
#define UNGAME_VECTOR_H_

#include <SDL2/SDL.h>
#include <math.h>
class Vector {
public:
  Vector();
  virtual ~Vector() = default;
  void draw(SDL_Renderer*);
  void setPos(const float*, const float*);
  void setAngle(const int*);
  int posX, posY, value, angleDeg;
  float angleRad;
};

#endif /* UNGAME_VECTOR_H_ */
