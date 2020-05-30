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

struct NeuralParams {
	uint16_t inputSize = 10;
	uint16_t hiddenSize = 100;
	uint16_t outputSize = 10;
	uint16_t maxConnections = 3;
	uint16_t fov = 45;
	double treshhold = 0.2;
};


class UNGNeuralNetwork {
public:

	UNGNeuralNetwork(const NeuralParams&);
	virtual ~UNGNeuralNetwork();
	void process();
	void draw(SDL_Renderer*);
	void kickInput(int);
	void handleMouseInput(Settings*);
	void clearInput();
	std::vector<UNGNeuron*> *output;
	uint8_t inputSize;

private:
//	uint8_t hiddenSize;
//	uint8_t outputSize;

	void searchNetworkByPos(std::vector<UNGNeuron*>*, SDL_Point*);
	UNGLogger *logger = LoggingHandler::getLogger("NeuralNet");
	void cleanupNetwork(std::vector<UNGNeuron*>*);
	std::vector<UNGNeuron*> *input;
	std::vector<UNGNeuron*> *hidden;
	UNGNeuron* generateHiddenNeuron(std::string, const NeuralParams&);
	void prepareNeuronConnections(UNGNeuron*, std::vector<UNGNeuron*>*, std::map<float, UNGNeuron*>&);
	void generateNeuronConnections(UNGNeuron*, std::map<float, UNGNeuron*>&, uint16_t);
};

#endif /* UNGNEURON_NET_H_ */
