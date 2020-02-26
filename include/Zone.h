#ifndef ZONE_H_
#define ZONE_H_

#include <vector>
#include <mutex>

#include "Creature.h"
class Zone {
public:
	int size = 100;
//	std::mutex mutex;
	std::vector<Creature*> *creatures;
	SDL_FPoint pos;
	Zone(int&, int&);
	virtual ~Zone();
	void update(Creature*);
	void draw (SDL_Renderer*);

private:
};

#endif /* ZONE_H_ */
