#include "UNGNeuronConnection.h"

UNGNeuronConnection::UNGNeuronConnection(SDL_FPoint pos, UNGNeuron* neuron) {
	externalPos = pos;
	this->neuron = neuron;
}

UNGNeuronConnection::~UNGNeuronConnection() {
	neuron = nullptr;
}

uint32_t UNGNeuronConnection::getColor(){
	return UNG_Globals::GREY_TRANSPARENT;
}
