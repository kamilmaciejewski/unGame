#ifndef UNGNEURON_NET_H_
#define UNGNEURON_NET_H_

#include <ctime>
#include <SDL2/SDL.h>
#include <vector>
#include <map>
#include <time.h>

#include "UNGNeuron.h"
#include "UNGLoggingHandler.h"
#include "UNGSettings.h"
#include "UNGGeometry.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "UNGNeuralParams.h"

class UNGNeuralNetwork {
public:

	UNGNeuralNetwork(NeuralParams);
	virtual ~UNGNeuralNetwork();
	void process();
	void draw(SDL_Renderer*);
	void kickInput(int);
	void handleMouseInput(Settings*);
	void clearInput();
	std::vector<UNGNeuron*> *output;
	float energyCost;
	NeuralParams params{nullptr,nullptr};

private:
	const float neuronEnergryCost = 0.01;
	const float connectionEnergyCost = 0.001;

	void searchNetworkByPos(std::vector<UNGNeuron*>*, SDL_Point*);
	UNGLogger *logger = LoggingHandler::getLogger("NeuralNet");
	void cleanupNetwork(std::vector<UNGNeuron*>*);
	std::vector<UNGNeuron*> *input;
	std::vector<UNGNeuron*> *hidden;
	UNGNeuron* generateHiddenNeuron(std::string, const NeuralParams&);
	void prepareNeuronConnections(UNGNeuron*, std::vector<UNGNeuron*>*,
			std::map<float, UNGNeuron*>&);
	void generateNeuronConnections(UNGNeuron*, std::map<float, UNGNeuron*>&,
			uint16_t);
};

#endif /* UNGNEURON_NET_H_ */
