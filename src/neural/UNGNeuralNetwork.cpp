#include "UNGNeuralNetwork.h"
#include <iostream>
using namespace UNG_Globals;
UNGNeuralNetwork::UNGNeuralNetwork() {
	input = new std::vector<UNGNeuron*>();
	input->reserve(inputSize);
	hidden = new std::vector<UNGNeuron*>();
	hidden->reserve(hiddenSize);
	output = new std::vector<UNGNeuron*>();

	for (uint8_t i = 0; i < inputSize; i++) {
		input->push_back(
				new UNGNeuron(
						SDL_FPoint { (float) neuralBox.x + 10,
								(float) (neuralBox.h / inputSize * (i))
										+ neuralBox.y + 10 },
						"i" + std::to_string(i), (float) 0));
	}
	for (uint8_t i = 0; i < hiddenSize; i++) {
		hidden->push_back(generateHiddenNeuron("h" + std::to_string(i)));
	}
	for (auto neuron : *hidden) {
		generateNeuronConnections(neuron, input);
	}
	for (uint8_t i = 0; i < outputSize; i++) {
		output->push_back(
				new UNGNeuron(
						SDL_FPoint { (float) (neuralBox.x + neuralBox.w - 10),
								(float) (neuralBox.h / outputSize * (i))
										+ neuralBox.y + 10 },
						"o" + std::to_string(i), (float) 0));
	}

}
void UNGNeuralNetwork::generateNeuronConnections(UNGNeuron *neuron,
		std::vector<UNGNeuron*> *network) {
	std::map<float, UNGNeuron*> connections;
	for (auto external : *network) {
		if (neuron->id != external->id)
			connections[100.0 / distance(neuron->pos, external->pos)] =
					external;
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
		posX = (float) neuralBox.x + 25 + (rand() % (neuralBox.w - 50));
		posY = (float) neuralBox.y + 5 + (rand()) % (neuralBox.h - 10);
		for (auto neuron : *hidden) {
			if (abs(posX - neuron->pos.x) < 20.0
					&& abs(posY - neuron->pos.y) < 20.0) {
				collide = true;
			}
		}
	} while (collide && ++collisionCount < 255);
	return new UNGNeuron(SDL_FPoint { (float) (posX), (float) (posY) }, id,
			(rand() % 50) - 115);

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
	SDL_SetRenderDrawColor(renderer, 88, 88, 88, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &(neuralBox));
	for (auto neuron : *hidden) {
		neuron->draw(renderer);
	}
	for (auto neuron : *input) {
		neuron->draw(renderer);
	}
	for (auto neuron : *output) {
			neuron->draw(renderer);
		}
}

UNGNeuralNetwork::~UNGNeuralNetwork() {
	cleanupNetwork(input);
	cleanupNetwork(hidden);
	cleanupNetwork(output);
	delete input;
	input = nullptr;
	delete hidden;
	hidden = nullptr;
	delete output;
	output = nullptr;
	delete logger;
	logger = nullptr;
}

void UNGNeuralNetwork::cleanupNetwork(std::vector<UNGNeuron*> *network) {
	if (network == nullptr) {
		return;
	}
	if (network->size() > 0) {
		for (auto neuron : *network) {
			if (neuron != nullptr)
				delete neuron;
		}
		network->clear();
	}
}
