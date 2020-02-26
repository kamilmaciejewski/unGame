#ifndef CREATURE_H_
#define CREATURE_H_

#include <string>

#include "SDL2_rotozoom.h"
#include "Object.h"

class Creature: public Object {

	const float fov = 45.0;
	const int view_dist = 100;
	const int rotation_step = 3;

public:
	Creature(SDL_Surface*);
	virtual ~Creature();

	void setRotationSpeed(float&);
	void setSpeed(float&);
	void setAlpha(int);
	void setActive();
	void setInactive();

	void draw(SDL_Renderer*, Settings*);
	void update(const uint32_t*, Settings*);
	void move(const uint32_t*);
	void rotate(const float&);
	bool lookAt(const SDL_FPoint*);

	bool isActive();
	std::string getInfo();

private:
	bool activeState = false;
	float speed = 0, rotation_speed = 0;
	int alpha = 0;
};

#endif /* CREATURE_H_ */
