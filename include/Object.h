#ifndef UNGAME_BASICOBJECT_H_
#define UNGAME_BASICOBJECT_H_

#include <SDL2/SDL.h>
#include "Vector.h"
#include "Settings.h"
#include "Drawable.h"
#include "Geometry.hpp"
#include "Vector.h"

class Object {

protected:

	drawable *drawable_ = new drawable;
	SDL_Surface *surface = nullptr;

	UNG_Vector *vect = new UNG_Vector { &pos };
	bool isObjectOnScreen(const int*, const int*) const;
public:
	SDL_FPoint pos;
	Object();
	virtual ~Object();
	void setPos(const SDL_FPoint&);
	drawable* getDrawable();
};

#endif /* UNGAME_BASICOBJECT_H_ */
