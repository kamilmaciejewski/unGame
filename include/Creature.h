#ifndef CREATURE_H_
#define CREATURE_H_

#include <SDL2/SDL.h>
#include <string>

#include "SDL2_rotozoom.h"
#include "Constants.h"

class Creature {
  std::string skin;
  SDL_Surface* surface = nullptr;
  SDL_Surface* optimized_surface = nullptr;
  SDL_Surface* rotated_Surface = nullptr;
  SDL_Rect rect_pos { 0, 0, 0, 0 };
  float rot_angle = 0, buffered_angle = 0;
  float pos_x = 0, pos_y = 0;
  float speed = 0, rotation_speed = 0;
  const int rotation_step = 2;
  bool isCreatureOnScreen();

public:
  Creature();
  virtual ~Creature();
  void draw(SDL_Surface *);
  void update(uint32_t &);
  void move(long);
  void setPos(int, int);
  void rotate(float);
  void setRotationSpeed(float);
  void setSpeed(float);
};

#endif /* CREATURE_H_ */
