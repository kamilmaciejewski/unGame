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
//  void setPos(const SDL_Point&);
  void setAngle(double*);
  void add(Vector*);
  void add(double*);
  double angleRad, angleDeg;
private:
  int posX, posY, value;
};

#endif /* UNGAME_VECTOR_H_ */
