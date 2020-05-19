#include "UNGNeuralNetwork.h"
#include  "UNGLoggingHandler.h"

UNGNeuralNetwork::UNGNeuralNetwork() {
	input = new std::vector<UNGNeuron*>();
	hidden = new std::vector<UNGNeuron*>();
	output = new std::vector<UNGNeuron*>();
}
void UNGNeuralNetwork::process(){

}


UNGNeuralNetwork::~UNGNeuralNetwork() {
	cleanupNetwork(input);
	cleanupNetwork(hidden);
	cleanupNetwork(output);
	delete input;
	delete hidden;
	delete output;
}

void UNGNeuralNetwork::cleanupNetwork(std::vector<UNGNeuron*> *network) {

	if (network->size() > 0) {
		for (auto neuron : *network) {
			delete neuron;
		}
		network->clear();
	}
}
