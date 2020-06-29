#include "UNGNeuronConnection.h"

UNGNeuronConnection::UNGNeuronConnection(SDL_FPoint pos, UNGNeuron* neuron, std::string id) {
	externalPos = pos;
	this->neuron = neuron;
	this->id = id;
}

UNGNeuronConnection::~UNGNeuronConnection() {
	neuron = nullptr;
}

uint32_t UNGNeuronConnection::getColor(){
	return UNG_Globals::GREY_TRANSPARENT;
}
