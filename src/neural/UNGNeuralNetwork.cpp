#include "UNGNeuralNetwork.h"
#include <iostream>
using namespace UNG_Globals;
UNGNeuralNetwork::UNGNeuralNetwork(NeuralParams params) {
	this->params = params;
	input = new std::vector<UNGNeuron*>();
	input->reserve(params.inputSize);
	hidden = new std::vector<UNGNeuron*>();
	hidden->reserve(params.hiddenSize);
	output = new std::vector<UNGNeuron*>();

	for (uint8_t i = 0; i < params.inputSize; i++) {
		input->push_back(
				new UNGNeuron(
						SDL_FPoint { (float) neuralBox.x + 10,
								(float) (neuralBox.h / params.inputSize * (i))
										+ neuralBox.y + 10 },
						"i" + std::to_string(i), (float) 0, 0,
						params.treshold));
	}
	for (uint8_t i = 0; i < params.hiddenSize; i++) {
		hidden->push_back(
				generateHiddenNeuron("h" + std::to_string(i), params));
	}

	for (uint8_t i = 0; i < params.outputSize; i++) {
		output->push_back(
				new UNGNeuron(
						SDL_FPoint { (float) (neuralBox.x + neuralBox.w - 10),
								(float) (neuralBox.h / params.outputSize * (i))
										+ neuralBox.y + 10 },
						"o" + std::to_string(i), (float) -90, params.fov,
						params.treshold));
	}

	std::map<float, UNGNeuron*> connections;
	for (auto neuron : *hidden) {
		prepareNeuronConnections(neuron, input, connections);
		prepareNeuronConnections(neuron, hidden, connections);
		generateNeuronConnections(neuron, connections, params.maxConnections);
		connections.clear();
	}
	for (auto neuron : *output) {
		prepareNeuronConnections(neuron, hidden, connections);
		generateNeuronConnections(neuron, connections, params.maxConnections);
		connections.clear();
	}
	int connectionsCount = 0;
	for (auto neuron : *hidden) {
		connectionsCount += neuron->connections->size();
	}
	for (auto neuron : *output) {
		connectionsCount += neuron->connections->size();
	}
	energyCost = (input->size() + hidden->size() + output->size())
			* neuronEnergryCost + connectionsCount * connectionEnergyCost;
}
void UNGNeuralNetwork::prepareNeuronConnections(UNGNeuron *neuron,
		std::vector<UNGNeuron*> *network,
		std::map<float, UNGNeuron*> &connections) {

	for (auto external : *network) {
		if (neuron->id != external->id) {
			float angle = radToDeg(
					atan2(external->pos.x - neuron->pos.x,
							external->pos.y - neuron->pos.y));
			if (abs(getDifference(neuron->vect.getAngleDeg(), angle))
					< neuron->fov) {
				connections[distance(neuron->pos, external->pos)] = external;
			}
		}
	}
}

void UNGNeuralNetwork::generateNeuronConnections(UNGNeuron *neuron,
		std::map<float, UNGNeuron*> &connections, uint16_t maxConnections) {
	std::map<float, UNGNeuron*>::iterator itr;
	u_int index = 0;
	for (itr = connections.begin(); itr != connections.end(); itr++) {
		if (++index > maxConnections) {
			return;
		}
		neuron->connections->push_back(
				std::make_pair(100.0 / itr->first,
						new UNGNeuronConnection(neuron->pos, itr->second,
								std::to_string(index))));
	}
}

UNGNeuron* UNGNeuralNetwork::generateHiddenNeuron(std::string id,
		const NeuralParams &params) {
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
			(rand() % 50) - 115, params.fov, params.treshold);

}
void UNGNeuralNetwork::process() {
	for (auto neuron : *hidden) {
		neuron->calculate();
	}
	for (auto neuron : *output) {
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
	if (id > 0 && id < params.inputSize) {
		input->at(id)->state = true;
	}
}

void UNGNeuralNetwork::handleMouseInput(Settings *settings) {
	if (settings->mark_active == true
			&& SDL_PointInRect(&settings->mousePos, &UNG_Globals::neuralBox)) {
		settings->mark_active = false;

		searchNetworkByPos(input, &settings->mousePos);
		searchNetworkByPos(hidden, &settings->mousePos);
		searchNetworkByPos(output, &settings->mousePos);

	}
}

void UNGNeuralNetwork::searchNetworkByPos(std::vector<UNGNeuron*> *layer,
		SDL_Point *pos) {
	bool found = false;
	for (auto neuron : *layer) {
		if (!found && SDL_PointInRect(pos, &neuron->rectPos)) {
			neuron->isActive = true;
			found = true;
		} else {
			neuron->isActive = false;
		}

	}
}

void UNGNeuralNetwork::draw(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 88, 88, 88, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &(neuralBox));
//	stringColor(renderer, pos.x, pos.y + 6, id.c_str(), getColor());
	stringColor(renderer, UNG_Globals::neuralBox.x, UNG_Globals::neuralBox.y,
			("in:"+std::to_string(params.inputSize)).c_str(), UNG_Globals::GREEN);
	stringColor(renderer, UNG_Globals::neuralBox.x, UNG_Globals::neuralBox.y+10,
				("hi:"+std::to_string(params.hiddenSize)).c_str(), UNG_Globals::GREEN);
	stringColor(renderer, UNG_Globals::neuralBox.x, UNG_Globals::neuralBox.y+20,
				("ou:"+std::to_string(params.outputSize)).c_str(), UNG_Globals::GREEN);
	stringColor(renderer, UNG_Globals::neuralBox.x, UNG_Globals::neuralBox.y+30,
				("fo:"+std::to_string(params.fov)).c_str(), UNG_Globals::GREEN);
	stringColor(renderer, UNG_Globals::neuralBox.x, UNG_Globals::neuralBox.y+40,
				("tr:"+std::to_string(params.treshold)).c_str(), UNG_Globals::GREEN);
	stringColor(renderer, UNG_Globals::neuralBox.x, UNG_Globals::neuralBox.y+50,
				("con:"+std::to_string(params.maxConnections)).c_str(), UNG_Globals::GREEN);
	stringColor(renderer, UNG_Globals::neuralBox.x, UNG_Globals::neuralBox.y+60,
				("con:"+std::to_string(energyCost)).c_str(), UNG_Globals::GREEN);

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
