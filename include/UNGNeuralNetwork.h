#ifndef UNGNEURON_NET_H_
#define UNGNEURON_NET_H_

#include <ctime>
#include <SDL2/SDL.h>
#include <vector>
#include <map>

#include "UNGNeuron.h"
#include "UNGLoggingHandler.h"
#include "UNGGeometry.hpp"

class UNGNeuralNetwork {
public:

	UNGNeuralNetwork();
	virtual ~UNGNeuralNetwork();
	void process();
	void draw(SDL_Renderer*);
	void kickInput(int);
	void clearInput();
	const uint8_t inputSize = 30;
	const uint8_t hiddenSize = 100;
	const uint8_t outputSize = 10;

private:
	UNGLogger *logger = LoggingHandler::getLogger("NeuralNet");
	void cleanupNetwork(std::vector<UNGNeuron*>*);
	std::vector<UNGNeuron*> *input;
	std::vector<UNGNeuron*> *hidden;
	std::vector<UNGNeuron*> *output;
	UNGNeuron* generateHiddenNeuron(std::string);
	void generateNeuronConnections(UNGNeuron*, std::vector<UNGNeuron*>*);
};

#endif /* UNGNEURON_NET_H_ */
