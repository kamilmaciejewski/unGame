#ifndef PLANT_H
#define PLANT_H

#include <UNGObject.h>
#include <string>

#include "SDL2_rotozoom.h"

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

private:
	bool activeState = false;
};

#endif /* PLANT_H */
