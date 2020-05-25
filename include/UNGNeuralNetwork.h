#ifndef UNGNEURON_NET_H_
#define UNGNEURON_NET_H_

#include <ctime>
#include <SDL2/SDL.h>
#include <vector>

#include "UNGNeuron.h"
#include "UNGLoggingHandler.h"
#include "UNGGeometry.hpp"

class UNGNeuralNetwork {
public:

	UNGNeuralNetwork();
	~UNGNeuralNetwork();
	void process();
	void draw(SDL_Renderer*);
	void kickInput(int);
	void clearInput();
	const uint8_t inputSize = 20;
	const uint8_t hiddenSize = 40;

private:
	UNGLogger *logger = LoggingHandler::getLogger("NeuralNet");
	void cleanupNetwork(std::vector<UNGNeuron*>*);
	std::vector<UNGNeuron*> *input;
	std::vector<UNGNeuron*> *hidden;
	std::vector<UNGNeuron*> *output;
};

#endif /* UNGNEURON_NET_H_ */
