#ifndef UNGAME_VECTOR_H_
#define UNGAME_VECTOR_H_

#include <SDL2/SDL.h>
#include <math.h>
#include <UNGGeometry.h>
class UNG_Vector {
public:
	UNG_Vector(SDL_FPoint*);
	UNG_Vector(SDL_FPoint*, float, float);
	virtual ~UNG_Vector() = default;
	void draw(SDL_Renderer*);
	void setVal(float);
	void setAngleDeg(float&);
	void setAngleRad(float&);
	void add(UNG_Vector*);
	void add(float*);
	float getAngleDeg();
	float getAngleRad();
	SDL_FPoint* pos; //TODO Private
	float value; //TODO Private
private:
	float angle;
};

#endif /* UNGAME_VECTOR_H_ */
