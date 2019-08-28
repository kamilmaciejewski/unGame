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
  void setAngle(float*);
  void add(Vector*);
  void add(float*);
private:
  int posX, posY, value;
  float angleRad, angleDeg;
};

#endif /* UNGAME_VECTOR_H_ */
