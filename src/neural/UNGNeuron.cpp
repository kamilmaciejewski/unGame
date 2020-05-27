#include <UNGNeuron.h>
#include <UNGNeuronConnection.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL2/SDL.h>

UNGNeuron::UNGNeuron(SDL_FPoint _pos, std::string id) {
	connections = new std::vector<std::pair<double, UNGNeuronConnection*>>();
	pos = _pos;
	this->id = id;
}

UNGNeuron::~UNGNeuron() {
	for(auto connection : *connections) {
		delete connection.second;
		connection.second = nullptr;
		connection.first = 0;
	}
	connections->clear();
	delete connections;
	connections = nullptr;
}
void UNGNeuron::draw(SDL_Renderer *renderer) {
//	for (auto connection : *connections) {
//		lineColor(renderer, pos.x, pos.y, connection.second->neuron->pos.x,
//				connection.second->neuron->pos.y,
//				connection.second->getColor());
//		stringColor(renderer, (connection.second->neuron->pos.x + pos.x) / 2,
//				(connection.second->neuron->pos.y + pos.y) / 2,
//				std::to_string(connection.first).c_str(),
//				connection.second->getColor());
//	}
	circleColor(renderer, pos.x, pos.y, 10, getColor());
	stringColor(renderer, pos.x, pos.y + 10, id.c_str(), getColor());
//	stringColor(renderer, pos.x, pos.y + 20,
//			("net:" + std::to_string(net)).c_str(), getColor());
//	stringColor(renderer, pos.x, pos.y + 30,
//			("sigm:" + std::to_string(sigmoid)).c_str(), getColor());
//	stringColor(renderer, pos.x, pos.y + 40,
//			("trsh:" + std::to_string(treshhold)).c_str(), getColor());

}

uint32_t UNGNeuron::getColor() {
	if (state) {
		return UNG_Globals::GREEN;
	}
	return UNG_Globals::RED;
}
void UNGNeuron::calculate() {
	double net = 0;
	for (auto connection : *connections) {
		if (connection.second->neuron->state) {
			net = net + connection.first;
		}
	}
	if ((1.0 / (1.0 + exp(net))) < treshhold) {
		state = true;
	} else {
		state = false;
	}
}
