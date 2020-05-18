#include <UNGNeuron.h>

UNGNeuron::UNGNeuron() {
	connections = new std::vector<std::pair<double, UNGNeuron*>>();
}

UNGNeuron::~UNGNeuron() {
	delete connections;
}

void UNGNeuron::calculate() {
	double net = 0;
	for (auto neuron : *connections) {
		net = net + (neuron.first * neuron.second->value);
	}
	value = 1.0 / (1.0 + exp(net));
}
