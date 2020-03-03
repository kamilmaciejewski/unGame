#include <SDL2/SDL.h>
#include <vector>
#include "Vector.h"
#include "Geometry.hpp"

struct drawable {
	SDL_Texture *texture;
	SDL_Rect rect_draw;
	float rot_angle;
};
