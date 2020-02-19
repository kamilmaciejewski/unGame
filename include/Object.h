#ifndef UNGAME_BASICOBJECT_H_
#define UNGAME_BASICOBJECT_H_

#include <SDL2/SDL.h>
#include "Vector.h"
#include "Settings.h"
#include "Drawable.h"
#include "Geometry.hpp"

class Object {

protected:

	drawable drawable_data;
	drawable *drawable_ = &drawable_data;
	SDL_Surface *surface = nullptr;

	SDL_FPoint pos;
	bool isObjectOnScreen(const int*, const int*) const;
public:
	Object();
	virtual ~Object();
	void setPos(const SDL_FPoint&);
	drawable* getDrawable();
};

#endif /* UNGAME_BASICOBJECT_H_ */
