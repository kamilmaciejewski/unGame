#include <SDL2/SDL.h>
#include <UNGGeometry.h>
#include <cmath>


float distance(const SDL_FPoint *from, const SDL_FPoint *to) {
	return sqrt((pow(from->x - to->x, 2) + pow(from->y - to->y, 2)));
}
float distance(SDL_FPoint from, SDL_FPoint to) {
	return sqrt((pow(from.x - to.x, 2) + pow(from.y - to.y, 2)));
}
float getDifference(float b1, float b2) {
	float r = fmod(b2 - b1, 360.0);
	if (r < -180.0)
		r += 360.0;
	if (r >= 180.0)
		r -= 360.0;
	return r;
}
