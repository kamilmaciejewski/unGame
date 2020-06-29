#include <UNGNeuron.h>
#include <UNGNeuronConnection.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL2/SDL.h>
using namespace std;
UNGNeuron::UNGNeuron(SDL_FPoint pos, std::string id, float angle, uint16_t fov,
		float treshold, float maxConnDist, float connWeightAngleFactor) {
	connections = new std::vector<std::pair<float, UNGNeuronConnection*>>();
	this->pos = pos;
	this->vect.setAngleDeg(angle);
	this->vect.setVal(maxConnDist);
	posDirection.x = pos.x+sin(vect.getAngleRad())*vect.value/30;
	posDirection.y = pos.y+cos(vect.getAngleRad())*vect.value/30;
	this->rectPos = { (int) pos.x - 5, (int) pos.y - 5, 10, 10 };
	this->id = id;
	this->fov = fov;
	this->treshhold = treshold;
	this->connWeightAngleFactor = connWeightAngleFactor;
}

UNGNeuron::~UNGNeuron() {
	for (auto connection : *connections) {
		delete connection.second;
		connection.second = nullptr;
		connection.first = 0;
	}
	connections->clear();
	delete connections;
	connections = nullptr;
}
void UNGNeuron::draw(SDL_Renderer *renderer) {
	if (isActive) {
//		stringColor(renderer, pos.x, pos.y + 6, id.c_str(), getColor());
		SDL_RenderDrawRect(renderer, &rectPos);
		for (auto connection : *connections) {
			lineColor(renderer, pos.x, pos.y, connection.second->neuron->pos.x,
					connection.second->neuron->pos.y,
					connection.second->getColor());
			stringColor(renderer,
					(connection.second->neuron->pos.x + pos.x) / 2,
					(connection.second->neuron->pos.y + pos.y) / 2,
					(connection.second->id + ": "
							+ std::to_string(connection.first)).c_str(),
					connection.second->getColor());

		}
		stringColor(renderer, pos.x, pos.y + 30,
				("net:" + std::to_string(net)).c_str(), getColor());
		stringColor(renderer, pos.x, pos.y + 40,
				("sigm:" + std::to_string(sigm)).c_str(), getColor());
		stringColor(renderer, pos.x, pos.y + 50,
				("trsh:" + std::to_string(treshhold)).c_str(), getColor());
		stringColor(renderer, pos.x, pos.y + 20, ("id:" + id).c_str(),
				getColor());
	}
	circleColor(renderer, pos.x, pos.y, 5, getColor());
	lineColor(renderer,pos.x, pos.y, posDirection.x, posDirection.y,getColor());

}

uint32_t UNGNeuron::getColor() {
	if (state) {
		return UNG_Globals::GREEN;
	}
	return UNG_Globals::RED;
}
void UNGNeuron::calculate() {
	calculateNet();
	calculateValue();
}
void UNGNeuron::calculateValue() {

	sigm = 1.0 / (1.0 + exp(net));
	if ((sigm) < treshhold) {
		treshhold -= 10*tresholdDelta;
		state = true;
	} else {
		treshhold += tresholdDelta;
		state = false;
	}
}
void UNGNeuron::resetNet() {
	net = 0;
}
void UNGNeuron::calculateNet() {
	resetNet();
	for (auto connection : *connections) {
		if (connection.second->neuron->state) {
			net = net + connection.first;
		}
	}
}
