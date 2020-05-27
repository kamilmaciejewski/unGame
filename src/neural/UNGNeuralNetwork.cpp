#include "UNGNeuralNetwork.h"
#include <iostream>

UNGNeuralNetwork::UNGNeuralNetwork() {
	input = new std::vector<UNGNeuron*>();
	input->reserve(inputSize);
	hidden = new std::vector<UNGNeuron*>();
	hidden->reserve(hiddenSize);
	output = new std::vector<UNGNeuron*>();

	for (uint8_t i = 0; i < inputSize; i++) {
		input->push_back(
				new UNGNeuron(
						SDL_FPoint { (float) 1100, (float) (25 * (i + 1)) },
						"in" + std::to_string(i)));
	}
	for (uint8_t i = 0; i < hiddenSize; i++) {

		hidden->push_back(generateHiddenNeuron("hi" + std::to_string(i)));
	}
	for (auto neuron : *hidden) {
		generateNeuronConnections(neuron, input);
	}

}
void UNGNeuralNetwork::generateNeuronConnections(UNGNeuron *neuron,
		std::vector<UNGNeuron*> *network) {
	std::map<float, UNGNeuron*> connections;
	for (auto external : *network) {
		if (neuron->id != external->id)
			connections[100.0/distance(neuron->pos, external->pos)] = external;
	}
	std::map<float, UNGNeuron*>::iterator itr;
	for (itr = connections.begin(); itr != connections.end(); itr++) {
		neuron->connections->push_back(
				std::make_pair(itr->first,
						new UNGNeuronConnection(neuron->pos, itr->second)));
	}
	connections.clear();

}
UNGNeuron* UNGNeuralNetwork::generateHiddenNeuron(std::string id) {
	float posX, posY;
	bool collide;
	uint8_t collisionCount = 0;
	do {
		collide = false;
		posX = (float) 1125 + (rand()) % 300;
		posY = (float) 25 + (rand()) % 25 * inputSize;
		for (auto neuron : *hidden) {
			if (abs(posX - neuron->pos.x) < 20.0
					&& abs(posY - neuron->pos.y) < 20.0) {
				collide = true;
			}
		}
	} while (collide && ++collisionCount < 255);
	return new UNGNeuron(SDL_FPoint { (float) (posX), (float) (posY) }, id);

}
void UNGNeuralNetwork::process() {
	for (auto neuron : *hidden) {
		neuron->calculate();
	}

}
void UNGNeuralNetwork::clearInput() {
	for (auto neuron : *input) {
		neuron->state = false;
	}

}

void UNGNeuralNetwork::kickInput(int id) {
	//TODO: This check will not be needed if relative vector will be passed from view.
	if (id < inputSize) {
		input->at(id)->state = true;
	}
}

void UNGNeuralNetwork::draw(SDL_Renderer *renderer) {
	for (auto neuron : *hidden) {
		neuron->draw(renderer);
	}
	for (auto neuron : *input) {
		neuron->draw(renderer);
	}
}

UNGNeuralNetwork::~UNGNeuralNetwork() {
	cleanupNetwork(input);
	cleanupNetwork(hidden);
	cleanupNetwork(output);
	delete input;
	input= nullptr;
	delete hidden;
	hidden = nullptr;
	delete output;
	output = nullptr;
	delete logger;
	logger = nullptr;
}

void UNGNeuralNetwork::cleanupNetwork(std::vector<UNGNeuron*> *network) {
	if(network == nullptr){
		return;
	}
	if (network->size() > 0) {
		for (auto neuron : *network) {
			if (neuron!=nullptr)
			delete neuron;
		}
		network->clear();
	}
}
