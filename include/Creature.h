#ifndef CREATURE_H_
#define CREATURE_H_

#include <string>

#include "SDL2_rotozoom.h"
#include "Object.h"
#include "Plant.h"

class Creature: public Object {

	const float FOV = 45.0;
	const int VIEW_DIST = 100;
	const int ROTATION_STEP = 3;
	float metabolism_factor = 0.05;
	const unsigned int MAX_VIEW_ENTRIES = 1000;

public:
	float energy = 255;
	std::vector<UNG_Vector*> *multiview;

	Creature(SDL_Surface*);
	virtual ~Creature();

	void setRotationSpeed(float&);
	void setSpeed(float&);
	void setActive();
	void setInactive();

	void draw(SDL_Renderer*, Settings*);
	void update(const uint32_t*, Settings*);
	void wrapScreenPos();
	void move(const uint32_t*);
	void rotate(const float&);

	bool isActive();
	bool isAlive();
	void cleanupView();
	std::string getInfo();
	bool lookAt(const Creature*);
	bool lookAt(const Plant*);

private:
	UNG_Vector* lookAt(const SDL_FPoint point);
	bool activeState = false;
	float speed = 0, rotation_speed = 0;
};

#endif /* CREATURE_H_ */
