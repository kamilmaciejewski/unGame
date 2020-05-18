#ifndef ZONE_H_
#define ZONE_H_

#include <UNGCreature.h>
#include <UNGPlant.h>
#include <vector>
#include <mutex>

class Zone {
public:
	int size = 100;
	std::vector<Creature*> *creatures;
	std::vector<Plant*> *plants;
	SDL_FPoint pos;

	Zone(unsigned int&, unsigned int&);
	virtual ~Zone();
	void update(Creature*);
	void update(Plant*);
	void kickOut(Creature*);
	void kickOut(Plant*);
	void draw (SDL_Renderer*);

private:
};

#endif /* ZONE_H_ */
