#ifndef UNGNEURON_H_
#define UNGNEURON_H_

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <UNGGlobals.h>

class UNGNeuron {
public:
	SDL_FPoint pos;
	int value = 0;
	std::string id;
	std::vector<std::pair<double, UNGNeuron*>> *connections;
	bool state = false;

	UNGNeuron(SDL_FPoint, std::string);
	virtual ~UNGNeuron();

	void calculate();
	void draw(SDL_Renderer*);
	uint32_t getColor();

private:
};

#endif /* UNGNEURON_H_ */
