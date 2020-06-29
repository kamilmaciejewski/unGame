#ifndef SRC_UNGAME_GEOMETRY_HPP_
#define SRC_UNGAME_GEOMETRY_HPP_

#include <SDL2/SDL.h>
const float f360 = 360.0, f180 = 180.0;
/**
 *  \brief  The structure that defines a point (double)
 */
// Converts degrees to radians.
#define degToRad(angleDegrees) (angleDegrees * M_PI / 180.0)

// Converts radians to degrees.
#define radToDeg(angleRadians) (angleRadians * 180.0 / M_PI)

float distance(const SDL_FPoint*, const SDL_FPoint*);
float distance(SDL_FPoint, SDL_FPoint);
float getAngleDifference(float, float);

SDL_bool SDL_FPointInRect(const SDL_FPoint*, const SDL_Rect*);
#endif /* SRC_UNGAME_GEOMETRY_HPP_ */
