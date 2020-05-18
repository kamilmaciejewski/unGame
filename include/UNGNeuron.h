#ifndef UNGNEURON_H_
#define UNGNEURON_H_

#include <SDL2/SDL.h>
#include <vector>

class UNGNeuron {
public:
	SDL_FPoint pos;
	int value = 0;
	std::vector<std::pair<double, UNGNeuron*>> *connections;

	UNGNeuron();
	virtual ~UNGNeuron();

	void calculate();

private:
};

#endif /* UNGNEURON_H_ */
