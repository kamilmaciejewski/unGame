#ifndef CREATURE_H_
#define CREATURE_H_

#include <string>

#include "SDL2_rotozoom.h"
#include "Object.h"

class Creature: public Object {

  float speed = 0, rotation_speed = 0, f360 = 360, f180 = 180;
  const int rotation_step = 3;

public:
  bool isActive = false;
  Creature(SDL_Surface*);
  virtual ~Creature();
  void draw(SDL_Renderer*, Settings*);
  void update(const uint32_t*, Settings*);
  void move(const uint32_t*);
  void rotate(const float&);
  void setRotationSpeed(float&);
  void setSpeed(float&);
  std::string getInfo();
};

#endif /* CREATURE_H_ */
