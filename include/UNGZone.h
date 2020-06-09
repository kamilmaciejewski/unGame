#ifndef ZONE_H_
#define ZONE_H_

#include <UNGCreature.h>
#include <UNGPlant.h>
#include <vector>
#include <thread>

class Zone {
public:
	int size = 100;
	std::vector<std::shared_ptr<Creature>> *creatures;
	std::vector<Plant*> *plants;
	SDL_FPoint pos;

	Zone(unsigned int&, unsigned int&);
	virtual ~Zone();
	void update(std::shared_ptr<Creature>);
	void update(Plant*);
	long kickOut(std::shared_ptr<Creature>);
	void kickOut(Plant*);
	void draw (SDL_Renderer*);

private:
};

#endif /* ZONE_H_ */
