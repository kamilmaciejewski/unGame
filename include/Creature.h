#ifndef CREATURE_H_
#define CREATURE_H_

#include "SDL2_rotozoom.h"
#include "BasicObject.h"

class Creature : public BasicObject {
  float rot_angle = 0;

  float speed = 0, rotation_speed = 0;
  const int rotation_step = 2;


public:
  bool isActive = false;
  Creature();
  virtual ~Creature();
  void draw(SDL_Renderer* , const int*, const int*);
  void update(const uint32_t*);
  void move(const uint32_t*);
  void rotate(float);
  void setRotationSpeed(float);
  void setSpeed(float);
};

#endif /* CREATURE_H_ */
