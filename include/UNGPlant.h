#ifndef PLANT_H
#define PLANT_H

#include <string>
#include "UNGObject.h"
#include "UNGGlobals.h"
#include "SDL2_gfxPrimitives.h"

class Plant: public Object {

public:
	Plant();
	virtual ~Plant();

	void setActive();
	void setInactive();

	void draw(SDL_Renderer*);
	void update();

	bool isActive();
	std::string getInfo();

	float energy = 255; //TODO: make private
private:
	bool activeState = false;
};

#endif /* PLANT_H */
