#ifndef PLANT_H
#define PLANT_H

#include <string>

#include "SDL2_rotozoom.h"
#include "Object.h"

class Plant: public Object {

//	const float fov = 45.0;
//	const int view_dist = 100;
//	const int rotation_step = 3;

public:
//	std::vector<UNG_Vector*> *multiview = new std::vector<UNG_Vector*>();
	Plant(SDL_Surface*);
	virtual ~Plant();

//	void setRotationSpeed(float&);
//	void setSpeed(float&);
//	void setAlpha(int);
	void setActive();
	void setInactive();

	void draw(SDL_Renderer*, Settings*);
	void update(const uint32_t*, Settings*);
//	void move(const uint32_t*);
//	void rotate(const float&);

	bool isActive();
	std::string getInfo();
//	bool lookAt(const Plant*);

private:
//	UNG_Vector* lookAt(const SDL_FPoint point);
	bool activeState = false;
//	float speed = 0, rotation_speed = 0;
//	int alpha = 0;
};

#endif /* PLANT_H */
