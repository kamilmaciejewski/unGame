#include <SDL2/SDL.h>
#include <UNGGeometry.hpp>
#include <UNGVector.h>
#include <vector>

struct Drawable {
	SDL_Texture *texture;
	SDL_Rect rect_draw;
	float rot_angle = 0;
};
