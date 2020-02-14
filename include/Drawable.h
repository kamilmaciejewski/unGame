#include <SDL2/SDL.h>
#include "Vector.h"

struct drawable {
  SDL_Texture* texture;
  SDL_Point pos;
  SDL_Rect rect_draw;
  double rot_angle;
  double view_angle;
  Vector vect, view_vect;
};
