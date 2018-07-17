#include <SDL2/SDL.h>
#include "Vector.h"

struct drawable{
  SDL_Texture* texture;
  SDL_Rect rect_pos;
  float rot_angle;
  Vector vect;
};
