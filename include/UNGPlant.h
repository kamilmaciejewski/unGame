#ifndef PLANT_H
#define PLANT_H

#include <string>
#include "UNGObject.h"
#include "UNGGlobals.h"
#include "SDL2_gfxPrimitives.h"
#include <atomic>

class Plant: public Object {

public:
	Plant(SDL_FPoint);
	virtual ~Plant();

	void draw(SDL_Renderer*);
	void update();

	bool isAlive();
	std::string getInfo();

	 std::atomic<float> energy = 512; //TODO: make private
private:
	 int size = 30;
};

#endif /* PLANT_H */
