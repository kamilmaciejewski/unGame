#include "UNGNeuralNetwork.h"

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
		float posX, posY;
		bool collide;
		uint8_t collisionCount=0;
		do {
			collide = false;
			posX = (float) 1150 + (rand()) % 300;
			posY = (float) 25 + (rand()) % 300;
			for (auto neuron : *hidden) {
				if (abs(posX - neuron->pos.x) < 20.0 && abs(posY - neuron->pos.y) < 20.0) {
					collide = true;
				}
			}
		} while (collide && ++collisionCount < 999);

		auto neuron = new UNGNeuron(
				SDL_FPoint { (float) (posX), (float) (posY) },
				"hi" + std::to_string(i));

		hidden->push_back(neuron);
	}
}
void UNGNeuralNetwork::process() {

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
	for (auto neuron : *input) {
		neuron->draw(renderer);
	}
	for (auto neuron : *hidden) {
		neuron->draw(renderer);
	}
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
