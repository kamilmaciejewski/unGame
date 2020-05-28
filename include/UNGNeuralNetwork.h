#ifndef UNGNEURON_NET_H_
#define UNGNEURON_NET_H_

#include <ctime>
#include <SDL2/SDL.h>
#include <vector>
#include <map>

#include "UNGNeuron.h"
#include "UNGLoggingHandler.h"
#include "UNGSettings.h"
#include "UNGGeometry.h"

class UNGNeuralNetwork {
public:

	UNGNeuralNetwork();
	virtual ~UNGNeuralNetwork();
	void process();
	void draw(SDL_Renderer*);
	void kickInput(int);
	void handleInput(Settings*);
	void clearInput();
	const uint8_t inputSize = 30;
	const uint8_t hiddenSize = 100;
	const uint8_t outputSize = 10;
	std::vector<UNGNeuron*> *output;

private:
	void searchNetworkByPos(std::vector<UNGNeuron*>*, SDL_Point*);
	UNGLogger *logger = LoggingHandler::getLogger("NeuralNet");
	void cleanupNetwork(std::vector<UNGNeuron*>*);
	std::vector<UNGNeuron*> *input;
	std::vector<UNGNeuron*> *hidden;
	UNGNeuron* generateHiddenNeuron(std::string);
	void prepareNeuronConnections(UNGNeuron*, std::vector<UNGNeuron*>*, std::map<float, UNGNeuron*>&);
	void generateNeuronConnections(UNGNeuron*, std::map<float, UNGNeuron*>&);
};

#endif /* UNGNEURON_NET_H_ */
