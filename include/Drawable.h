#include <SDL2/SDL.h>
#include "Vector.h"

struct drawable {
  SDL_Texture* texture;
  SDL_Point pos;
  SDL_Rect rect_draw;
  float rot_angle;
  Vector vect;
};
