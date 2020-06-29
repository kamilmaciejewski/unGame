#include "UNGNeuralNetwork.h"
#include <iostream>
using namespace UNG_Globals;
UNGNeuralNetwork::UNGNeuralNetwork(const UNGNeuralNetwork &network) {
	params = network.params;
	params.randomize();
	input = new vector<UNGNeuron*>();
	input->reserve(params.inputSize);
	hidden = new vector<UNGNeuron*>();
	hidden->reserve(params.hiddenSize);
	output = new vector<UNGNeuron*>();
	output->reserve(params.outputSize);

	generateOutputLayer();

	for (uint16_t i = 0; i < params.inputSize; i++) {
			if (i < network.input->size()) {
				input->push_back(generateNeuron(network.input->at(i), neuralBoxInput));
			} else {
				input->push_back(generateHiddenNeuron("i" + to_string(i)));
			}
		}

	for (uint16_t i = 0; i < params.hiddenSize; i++) {
		if (i < network.hidden->size()) {
			hidden->push_back(generateNeuron(network.hidden->at(i), neuralBoxHidden));
		} else {
			hidden->push_back(generateHiddenNeuron("h" + to_string(i)));
		}
	}

	for (auto neuron : *hidden) {
		for (auto parentNeuron : *network.hidden) {
			if (parentNeuron->id == neuron->id) {
				copyNeuronConnections(parentNeuron, neuron);
				if (neuron->connections->size() < params.maxConnections) {
					map<float, UNGNeuron*> connections;
					prepareNeuronConnections(neuron, input, connections);
					prepareNeuronConnections(neuron, hidden, connections);
					generateNeuronConnections(neuron, connections);
				}
			}
		}
	}

	map<float, UNGNeuron*> connections;
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
	input = new vector<UNGNeuron*>();
	input->reserve(params.inputSize);
	hidden = new vector<UNGNeuron*>();
	hidden->reserve(params.hiddenSize);
	output = new vector<UNGNeuron*>();
	output->reserve(params.outputSize);

	generateInputLayer();
	generateOutputLayer();

	for (uint16_t i = 0; i < params.hiddenSize; i++) {
		hidden->push_back(generateHiddenNeuron("h" + to_string(i)));
	}

	map<float, UNGNeuron*> connections;
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
		vector<UNGNeuron*> *network,
		map<float, UNGNeuron*> &connections) {

	for (auto external : *network) {
		if (neuron->id != external->id) {
			float angle = radToDeg(
					atan2(external->pos.x - neuron->pos.x,
							external->pos.y - neuron->pos.y));
			float angleRelative = abs(
					getAngleDifference(neuron->vect.getAngleDeg(), angle));
			auto connDistance = distance(neuron->pos, external->pos);
			if (angleRelative < neuron->fov
					&& connDistance < neuron->vect.value) { //TODO: Getter for vect.value as connMAxDistance
				float connWeithAngleFactor = (angleRelative / neuron->fov)
						* neuron->connWeightAngleFactor;
				float distDelta = connDistance * connWeithAngleFactor;
				connections[connDistance - distDelta] = external;
			}
		}
	}
}

UNGNeuron* findNeuronById(const string &id, vector<UNGNeuron*> *vector) {
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
		if (!params.randomizeChance(params.connectionCopyChance)) {
			continue;
		}
		bool found = false;
		for (auto neuron : *input) {
			if (neuron->id == connection.second->neuron->id
					&& destination->connections->size()
							< params.maxConnections) {
				destination->connections->push_back(
						make_pair(params.randomizeVal(connection.first),
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
						make_pair(connection.first,
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
						make_pair(connection.first,
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
		map<float, UNGNeuron*> &connections) {
	map<float, UNGNeuron*>::iterator itr;
	u_int64_t index = 0;
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
					make_pair(100.0 / itr->first,
							new UNGNeuronConnection(neuron->pos, itr->second,
									to_string(index))));
		}
	}
}

void UNGNeuralNetwork::generateInputLayer() {
	for (uint16_t i = 0; i < this->params.inputSize; i++) {
		input->push_back(generateInputNeuron("i" + to_string(i)));
	}
}
void UNGNeuralNetwork::generateOutputLayer() {
	for (uint16_t i = 0; i < params.outputSize; i++) {
		output->push_back(
				new UNGNeuron(
						SDL_FPoint { (float) (neuralBox.x + neuralBox.w - 10),
								(float) (neuralBox.h / params.outputSize * (i))
										+ neuralBox.y + 10 },
						"o" + to_string(i), (float) -90, params.neuronFov,
						params.treshold, params.maxConnectionDistance, params.connWeightAngleFactor)); //TODO: randomize?
	}
}
UNGNeuron* UNGNeuralNetwork::generateInputNeuron(string id){
	auto posX = (float) neuralBoxInput.x + 25
			+ (rand() % (neuralBoxInput.w - 50));
	auto posY = (float) neuralBoxInput.y + 5
			+ (rand()) % (neuralBoxInput.h - 10);
	return
			new UNGNeuron(
					SDL_FPoint { posX, posY }, id,
					(float) 0, 0, params.treshold,0.0, 0.0);

}

UNGNeuron* UNGNeuralNetwork::generateNeuron(UNGNeuron *base, const SDL_Rect& box) {
	auto posX = params.randomizeVal(base->pos.x);
	auto posY = params.randomizeVal(base->pos.y);

	if (posX < box.x) {
		posX = box.x;
	} else if (posX > (box.x + box.w)) {
		posX = box.x + box.w;
	}
	if (posY < box.y) {
		posY = box.y;
	} else if (posY > (box.y + box.h)) {
		posY = box.y + box.h;
	}
	return new UNGNeuron(SDL_FPoint { posX, posY }, base->id,
			base->vect.getAngleDeg(), params.randomizeVal(base->fov),
			params.randomizeVal(base->treshhold),
			params.randomizeVal(base->vect.value),
			params.randomizeVal(base->connWeightAngleFactor));

}
UNGNeuron* UNGNeuralNetwork::generateHiddenNeuron(string id) {
	float posX, posY;
	bool collide;
	uint16_t collisionCount = 0;
	do {
		collide = false;
		posX = (float) neuralBoxHidden.x + 25 + (rand() % (neuralBoxHidden.w - 50));
		posY = (float) neuralBoxHidden.y + 5 + (rand()) % (neuralBoxHidden.h - 10);
		for (auto neuron : *hidden) {
			if (abs(posX - neuron->pos.x) < 20.0
					&& abs(posY - neuron->pos.y) < 20.0) {
				collide = true;
			}
		}
	} while (collide && ++collisionCount < 255);
	return new UNGNeuron(SDL_FPoint { (float) (posX), (float) (posY) }, id,
			(rand() % 50) - 115, params.neuronFov,
			params.randomizeVal(params.treshold),
			params.randomizeVal(params.maxConnectionDistance),
			params.randomizeVal(params.connWeightAngleFactor));

}
void UNGNeuralNetwork::process() {
	avgHiddenTreshhlold = 0.0;
	for (auto neuron : *hidden) {
		neuron->calculate();
		avgHiddenTreshhlold += neuron->treshhold;
	}
	avgOutputTreshhlold = 0.0;
	for (auto neuron : *output) {
		neuron->calculate();
		avgOutputTreshhlold += neuron->treshhold;
	}
	avgHiddenTreshhlold = avgHiddenTreshhlold / hidden->size();
	avgOutputTreshhlold = avgOutputTreshhlold / output->size();
}
void UNGNeuralNetwork::clearInput() {
	for (auto neuron : *input) {
//		neuron->resetNet();
		neuron->state = false;
	}

}
//void UNGNeuralNetwork::updateInput() {
//	for (auto neuron : *input) {
//		neuron->calculateValue();
//	}
//}

void UNGNeuralNetwork::kickInput(int id) {
	//TODO: This check will not be needed if relative vector will be passed from view.
	if (id > 0 && id < params.inputSize) {
		input->at(id)->state = true;
	}
}
	void UNGNeuralNetwork::kickFoodFoundFactor(){
		foodFound = true;
	}
void UNGNeuralNetwork::kickInput(const float &relativeAngle,
		const float &value) {

	auto lVal = relativeAngle / params.sightFov; //-1 to +1

	for (auto neuron : *input) {
		//X = (2B/C) -1
		auto posY = neuron->pos.y;
		auto yRange = neuralBoxInput.h;
		float y = (2 * posY / yRange) - 1;
		auto yMin = y - params.sightSharpness;
		auto yMax = y + params.sightSharpness;
		auto distval = value / params.viewDist;
		auto x = 1-((neuron->pos.x - neuralBoxInput.x) / neuralBoxInput.w);
		if (yMin < lVal && yMax > lVal) {
//			neuron->net = distval;
//			neuron->treshhold = x;
			if (distval < x) {
				neuron->state = true;
			}
//			neuron->net += (1-(distval*x));
		}
//		if (neuron->pos.x<)
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

void UNGNeuralNetwork::searchNetworkByPos(vector<UNGNeuron*> *layer,
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

void drawBox(SDL_Renderer *renderer, const SDL_Rect * rect, const char* title){
	SDL_RenderDrawRect(renderer, rect);
	stringColor(renderer, rect->x + 5,
				rect->y+5,
				title,
				UNG_Globals::GREY_TRANSPARENT);
}
void drawParamString(SDL_Renderer *renderer, const string title, int& yOffset) {
	stringColor(renderer, UNG_Globals::neuralBox.x + 10,
				UNG_Globals::neuralBox.y+ (yOffset+=10),
				title.c_str(),
				UNG_Globals::GREEN);
}

void UNGNeuralNetwork::draw(SDL_Renderer *renderer) {
	SDL_SetRenderDrawColor(renderer, 88, 88, 88, SDL_ALPHA_OPAQUE);
	drawBox(renderer,&(neuralBox),neuralBoxTitle);
	drawBox(renderer,&(neuralBoxInput),neuralBoxInputTitle);
	drawBox(renderer,&(neuralBoxHidden),neuralBoxHiddenTitle);
	drawBox(renderer,&(neuralBoxOutput),neuralBoxOutputTitle);


//	stringColor(renderer, pos.x, pos.y + 6, id.c_str(), getColor());

	int yOffset = 30;
	drawParamString(renderer, "input: " + to_string(params.inputSize), yOffset);
	drawParamString(renderer, "hidden: " + to_string(params.hiddenSize), yOffset);
	drawParamString(renderer, "output: " + to_string(params.outputSize), yOffset);
	drawParamString(renderer, "treshold: " + to_string(params.treshold), yOffset);
	drawParamString(renderer, "avg hiden treshold: " + to_string(avgHiddenTreshhlold), yOffset);
	drawParamString(renderer, "avg output treshold: " + to_string(avgOutputTreshhlold), yOffset);
	drawParamString(renderer, "connections:" + to_string(params.maxConnections), yOffset);
	drawParamString(renderer, "energy cost:" + to_string(energyCost), yOffset);
	drawParamString(renderer, "speed: " + to_string(params.speed), yOffset);
	drawParamString(renderer, "view dist: " + to_string(params.viewDist), yOffset);
	drawParamString(renderer, "conn copy chance: " + to_string(params.connectionCopyChance), yOffset);

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

void UNGNeuralNetwork::cleanupNetwork(vector<UNGNeuron*> *network) {
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
