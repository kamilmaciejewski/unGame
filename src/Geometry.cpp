#include <SDL2/SDL.h>
#include <UNGGeometry.h>
#include <cmath>


float distance(const SDL_FPoint *from, const SDL_FPoint *to) {
	return sqrt((pow(from->x - to->x, 2) + pow(from->y - to->y, 2)));
}
float distance(SDL_FPoint from, SDL_FPoint to) {
	return sqrt((pow(from.x - to.x, 2) + pow(from.y - to.y, 2)));
}
float getAngleDifference(float b1, float b2) {
	float r = fmod(b2 - b1, 360.0);
	if (r < -180.0)
		r += 360.0;
	if (r >= 180.0)
		r -= 360.0;
	return r;
}
SDL_bool SDL_FPointInRect(const SDL_FPoint *p, const SDL_Rect *r)
{
    return ( (p->x >= r->x) && (p->x < (r->x + r->w)) &&
             (p->y >= r->y) && (p->y < (r->y + r->h)) ) ? SDL_TRUE : SDL_FALSE;
}

