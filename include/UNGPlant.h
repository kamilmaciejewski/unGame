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

	 std::atomic<float> energy = startEnergy; //TODO: make private

	 float startEnergy = 200; //TODO: make private
	 SDL_Rect rect_food;
private:
	 int sizeFactor = 5;
};

#endif /* PLANT_H */
