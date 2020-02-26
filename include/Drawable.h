#include <SDL2/SDL.h>
#include <vector>
#include "Vector.h"
#include "Geometry.hpp"

struct drawable {
	SDL_Texture *texture;
	SDL_FPoint *pos = new SDL_FPoint { 0, 0 };
	SDL_Rect rect_draw;
	float rot_angle;
	float view_angle;
	UNG_Vector *vect = new UNG_Vector { pos };
	std::vector<UNG_Vector*> *multiview = new std::vector<UNG_Vector*>();
};
