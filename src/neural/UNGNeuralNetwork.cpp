#include "UNGNeuralNetwork.h"
#include <iostream>
using namespace UNG_Globals;
UNGNeuralNetwork::UNGNeuralNetwork(const UNGNeuralNetwork &network) {
	params = network.params;
	params.randomize();
	input = new std::vector<UNGNeuron*>();
	input->reserve(params.inputSize);
	hidden = new std::vector<UNGNeuron*>();
	hidden->reserve(params.hiddenSize);
	output = new std::vector<UNGNeuron*>();
	output->reserve(params.outputSize);

	generateInputLayer();
	generateOutputLayer();

	for (uint8_t i = 0; i < params.hiddenSize; i++) {
		if (i < network.hidden->size()) {
			hidden->push_back(generateHiddenNeuron(network.hidden->at(i)));
		} else {
			hidden->push_back(generateHiddenNeuron("h" + std::to_string(i)));
		}
	}

	for (auto neuron : *hidden) {
		for (auto parentNeuron : *network.hidden) {
			if (parentNeuron->id == neuron->id) {
				copyNeuronConnections(parentNeuron, neuron);
				if (neuron->connections->size() < params.maxConnections) {
					std::map<float, UNGNeuron*> connections;
					prepareNeuronConnections(neuron, input, connections);
					prepareNeuronConnections(neuron, hidden, connections);
					generateNeuronConnections(neuron, connections);
				}
			}
		}
	}

	std::map<float, UNGNeuron*> connections;
	for (auto neuron : *output) {
		prepareNeuronConnections(neuron, hidden, connections);
		generateNeuronConnections(neuron, connections);
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
UNGNeuralNetwork::UNGNeuralNetwork(NeuralParams params_) {
	this->params = params_;
	this->params.randomize();
	input = new std::vector<UNGNeuron*>();
	input->reserve(params.inputSize);
	hidden = new std::vector<UNGNeuron*>();
	hidden->reserve(params.hiddenSize);
	output = new std::vector<UNGNeuron*>();
	output->reserve(params.outputSize);

	generateInputLayer();
	generateOutputLayer();

	for (uint8_t i = 0; i < params.hiddenSize; i++) {
		hidden->push_back(generateHiddenNeuron("h" + std::to_string(i)));
	}

	std::map<float, UNGNeuron*> connections;
	for (auto neuron : *hidden) {
		prepareNeuronConnections(neuron, input, connections);
		prepareNeuronConnections(neuron, hidden, connections);
		generateNeuronConnections(neuron, connections);
		connections.clear();
	}
	for (auto neuron : *output) {
		prepareNeuronConnections(neuron, hidden, connections);
		generateNeuronConnections(neuron, connections);
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
UNGNeuron* findNeuronById(const string &id, std::vector<UNGNeuron*> *vector) {
	for (auto neur : *vector) {
		if (neur->id == id) {
			return neur;
		}
	}
	return nullptr;
}
void UNGNeuralNetwork::copyNeuronConnections(const UNGNeuron *source,
		UNGNeuron *destination) {
	for (auto connection : *source->connections) {
		bool found = false;
		for (auto neuron : *input) {
			if (neuron->id == connection.second->neuron->id
					&& destination->connections->size()
							< params.maxConnections) {
				destination->connections->push_back(
						std::make_pair(params.randomizeVal(connection.first),
								new UNGNeuronConnection(destination->pos,
										neuron, connection.second->id)));
				found = true;
				break;
			}
			if (found) {
				continue;
			}
		}
		for (auto neuron : *hidden) {
			if (neuron->id == connection.second->neuron->id
					&& destination->connections->size()
							< params.maxConnections) {
				destination->connections->push_back(
						std::make_pair(connection.first,
								new UNGNeuronConnection(destination->pos,
										neuron, connection.second->id)));
				found = true;
				break;
			}

		}
		if (found) {
			continue;
		}
		for (auto neuron : *output) {
			if (neuron->id == connection.second->neuron->id
					&& destination->connections->size()
							< params.maxConnections) {
				destination->connections->push_back(
						std::make_pair(connection.first,
								new UNGNeuronConnection(destination->pos,
										neuron, connection.second->id)));
				break;
			}
		}

	}
//	logger->log("Source had " + to_string(source->connections->size()));
//	logger->log("Limit: " + to_string(params.maxConnections));
//	logger->log("Copied " + to_string(destination->connections->size()));
}
void UNGNeuralNetwork::generateNeuronConnections(UNGNeuron *neuron,
		std::map<float, UNGNeuron*> &connections) {
	std::map<float, UNGNeuron*>::iterator itr;
	u_int index = 0;
	for (itr = connections.begin(); itr != connections.end(); itr++) {
		if (++index > params.maxConnections) {
			return;
		}
//			logger->log("Neuron: " + neuron->id + " has: " + to_string(neuron->connections->size()) + " connections");
//			logger->log("Neuron: " + neuron->id + " limit: " + to_string(params.maxConnections) + " connections");
		bool isAlreadyConnected = false;
		for (auto connection : *neuron->connections) {
			if (connection.second->neuron->id == itr->second->id)
				isAlreadyConnected = true;
		}
		if (!isAlreadyConnected) {
//			logger->log(
//					"Added new connection: " + neuron->id + ":"
//							+ to_string(index));
			neuron->connections->push_back(
					std::make_pair(100.0 / itr->first,
							new UNGNeuronConnection(neuron->pos, itr->second,
									std::to_string(index))));
		}
	}
}

void UNGNeuralNetwork::generateInputLayer() {
	for (uint8_t i = 0; i < this->params.inputSize; i++) {
		input->push_back(
				new UNGNeuron(
						SDL_FPoint { (float) neuralBoxInput.x + 10,
								(float) ((neuralBoxInput.h - 200)
										/ params.inputSize * (i))
										+ neuralBoxInput.y + 100 },
						"i" + std::to_string(i), (float) 0, 0,
						params.treshold));
	}
}
void UNGNeuralNetwork::generateOutputLayer() {
	for (uint8_t i = 0; i < params.outputSize; i++) {
		output->push_back(
				new UNGNeuron(
						SDL_FPoint { (float) (neuralBox.x + neuralBox.w - 10),
								(float) (neuralBox.h / params.outputSize * (i))
										+ neuralBox.y + 10 },
						"o" + std::to_string(i), (float) -90, params.neuronFov,
						params.treshold));
	}
}

UNGNeuron* UNGNeuralNetwork::generateHiddenNeuron(UNGNeuron *base) {
	auto posX = params.randomizeVal(base->pos.x);
	auto posY = params.randomizeVal(base->pos.y);

	if (posX < neuralBox.x) {
		posX = neuralBox.x;
	} else if (posX > (neuralBox.x + neuralBox.w)) {
		posX = neuralBox.x + neuralBox.w;
	}
	if (posY < neuralBox.y) {
		posY = neuralBox.y;
	} else if (posY > (neuralBox.y + neuralBox.h)) {
		posY = neuralBox.y + neuralBox.h;
	}
	return new UNGNeuron(SDL_FPoint { posX, posY }, base->id,
			base->vect.getAngleDeg(), params.randomizeVal(base->fov), params.randomizeVal(base->treshhold));

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
			(rand() % 50) - 115, params.neuronFov,
			params.randomizeVal(params.treshold));

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
	SDL_RenderDrawRect(renderer, &(neuralBoxInput));
//	stringColor(renderer, pos.x, pos.y + 6, id.c_str(), getColor());
	stringColor(renderer, UNG_Globals::neuralBox.x + 50,
			UNG_Globals::neuralBox.y,
			("input: " + std::to_string(params.inputSize)).c_str(),
			UNG_Globals::GREEN);
	stringColor(renderer, UNG_Globals::neuralBox.x + 50,
			UNG_Globals::neuralBox.y + 10,
			("hidden: " + std::to_string(params.hiddenSize)).c_str(),
			UNG_Globals::GREEN);
	stringColor(renderer, UNG_Globals::neuralBox.x + 50,
			UNG_Globals::neuralBox.y + 20,
			("output: " + std::to_string(params.outputSize)).c_str(),
			UNG_Globals::GREEN);
	stringColor(renderer, UNG_Globals::neuralBox.x + 50,
			UNG_Globals::neuralBox.y + 30,
			("fov: " + std::to_string(params.neuronFov)).c_str(),
			UNG_Globals::GREEN);
	stringColor(renderer, UNG_Globals::neuralBox.x + 50,
			UNG_Globals::neuralBox.y + 40,
			("treshold: " + std::to_string(params.treshold)).c_str(),
			UNG_Globals::GREEN);
	stringColor(renderer, UNG_Globals::neuralBox.x + 50,
			UNG_Globals::neuralBox.y + 50,
			("connections:" + std::to_string(params.maxConnections)).c_str(),
			UNG_Globals::GREEN);
	stringColor(renderer, UNG_Globals::neuralBox.x + 50,
			UNG_Globals::neuralBox.y + 60,
			("energy cost:" + std::to_string(energyCost)).c_str(),
			UNG_Globals::GREEN);
	stringColor(renderer, UNG_Globals::neuralBox.x + 50,
			UNG_Globals::neuralBox.y + 70,
			("speed: " + std::to_string(params.speed)).c_str(),
			UNG_Globals::GREEN);
	stringColor(renderer, UNG_Globals::neuralBox.x + 50,
			UNG_Globals::neuralBox.y + 80,
			("view dist: " + std::to_string(params.viewDist)).c_str(),
			UNG_Globals::GREEN);

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
