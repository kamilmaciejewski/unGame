#include <UNGNeuron.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL2/SDL.h>

UNGNeuron::UNGNeuron(SDL_FPoint _pos, std::string id) {
	connections = new std::vector<std::pair<double, UNGNeuron*>>();
	pos = _pos;
	this->id = id;
}

UNGNeuron::~UNGNeuron() {
	delete connections;
}
void UNGNeuron::draw(SDL_Renderer* renderer) {
	circleColor(renderer, pos.x, pos.y, 10, getColor());
	stringColor(renderer,pos.x,pos.y+10 , id.c_str(), getColor());

}

uint32_t UNGNeuron::getColor(){
	if(state){
	return UNG_Globals::GREEN;
	}
		return UNG_Globals::RED;
}
void UNGNeuron::calculate() {
	double net = 0;
	for (auto neuron : *connections) {
		net = net + (neuron.first * neuron.second->value);
	}
	value = 1.0 / (1.0 + exp(net));
}
