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
#include "UNGVector.h"

class UNGNeuralNetwork {
public:
	UNGNeuralNetwork(const UNGNeuralNetwork&);
	UNGNeuralNetwork(NeuralParams);
	virtual ~UNGNeuralNetwork();
	void process();
	void draw(SDL_Renderer*);
	void kickInput(int);
	void kickFoodFoundFactor();
	void kickInput(const float&, const float&);
	void handleMouseInput(Settings*);
	void clearInput();
	void updateInput();
	std::vector<UNGNeuron*> *output;
	float energyCost;
	NeuralParams params{nullptr,nullptr};
	bool foodFound = false;
	float avgHiddenTreshhlold = 0; //TODO: Private
	float avgOutputTreshhlold = 0; //TODO: Private

private:
	const float neuronEnergryCost = 0.01;
	const float connectionEnergyCost = 0.001;

	void searchNetworkByPos(std::vector<UNGNeuron*>*, SDL_Point*);
	UNGLogger *logger = LoggingHandler::getLogger("NeuralNet");
	void cleanupNetwork(std::vector<UNGNeuron*>*);
	std::vector<UNGNeuron*> *input;
	std::vector<UNGNeuron*> *hidden;
	void generateInputLayer();
	void generateOutputLayer();
	UNGNeuron* generateNeuron(UNGNeuron*, const SDL_Rect&);
	UNGNeuron* generateHiddenNeuron(std::string);
	UNGNeuron* generateInputNeuron(std::string);
	void prepareNeuronConnections(UNGNeuron*, std::vector<UNGNeuron*>*,
			std::map<float, UNGNeuron*>&);
	void generateNeuronConnections(UNGNeuron*, std::map<float, UNGNeuron*>&);
	void copyNeuronConnections(const UNGNeuron*, UNGNeuron*);
};

#endif /* UNGNEURON_NET_H_ */
