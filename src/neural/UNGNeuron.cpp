#include <UNGNeuron.h>
#include <UNGNeuronConnection.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL2/SDL.h>

UNGNeuron::UNGNeuron(SDL_FPoint pos, std::string id, float angle) {
	connections = new std::vector<std::pair<double, UNGNeuronConnection*>>();
	this->pos = pos;
	this->rectPos = { (int) pos.x - 5, (int) pos.y - 5, 10, 10 };
	this->id = id;
	this->vect.setAngleDeg(angle);
	this->vect.setVal((float) 10);
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
				stringColor(renderer, pos.x, pos.y + 20,
						("net:" + std::to_string(net)).c_str(), getColor());
				stringColor(renderer, pos.x, pos.y + 30,
						("sigm:" + std::to_string(sigm)).c_str(), getColor());
				stringColor(renderer, pos.x, pos.y + 40,
						("trsh:" + std::to_string(treshhold)).c_str(), getColor());

		}
	}
	circleColor(renderer, pos.x, pos.y, 5, getColor());
	stringColor(renderer, pos.x, pos.y + 6, id.c_str(), getColor());
	vect.draw(renderer);

}

uint32_t UNGNeuron::getColor() {
	if (state) {
		return UNG_Globals::GREEN;
	}
	return UNG_Globals::RED;
}
void UNGNeuron::calculate() {
	net = 0;
	for (auto connection : *connections) {
		if (connection.second->neuron->state) {
			net = net + connection.first;
		}
	}
	sigm = 1.0 / (1.0 + exp(net));
	if ((sigm) < treshhold) {
		state = true;
	} else {
		state = false;
	}
}
