#ifndef UNGNEURON_NET_H_
#define UNGNEURON_NET_H_

#include <vector>
#include <SDL2/SDL.h>

#include "UNGNeuron.h"

class UNGNeuralNetwork {
public:

	UNGNeuralNetwork();
	~UNGNeuralNetwork();

private:
	void cleanupNetwork(std::vector<UNGNeuron*>*);
	std::vector<UNGNeuron*> *input;
	std::vector<UNGNeuron*> *hidden;
	std::vector<UNGNeuron*> *output;
};

#endif /* UNGNEURON_NET_H_ */
