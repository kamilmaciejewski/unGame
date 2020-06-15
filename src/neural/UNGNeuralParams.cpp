#include "UNGNeuralParams.h"

NeuralParams::NeuralParams(std::default_random_engine *generator,
		std::normal_distribution<double> *distribution) {
	this->generator = generator;
	this->distribution = distribution;
}

float NeuralParams::randomizeVal(float val) {
	if (randomizeChance(15)) {
		auto distr = *distribution;
		float res = val + val / 10 * (distr(*generator));
		return res;
	} else {
		return val;
	}
}
void NeuralParams::randomize() {

	auto distr = *distribution;
	if(randomizeChance(15)){inputSize += inputSize / 3 * (distr(*generator));}
	if(randomizeChance(15)){hiddenSize += hiddenSize / 3 * (distr(*generator));}
	if(randomizeChance(15)){outputSize += outputSize / 3 * (distr(*generator));}
	if(randomizeChance(15)){maxConnections += maxConnections / 3 * (distr(*generator));}
	if(randomizeChance(15)){neuronFov += neuronFov / 3 * (distr(*generator));}
	if(randomizeChance(15)){treshold += treshold / 3 * (distr(*generator));}
	if(randomizeChance(15)){speed += speed / 2 * (distr(*generator));}
	if(randomizeChance(15)){speedFactor += speedFactor / 2 * (distr(*generator));}
	if(randomizeChance(15)){rotationFactor += rotationFactor / 2 * (distr(*generator));}
	if(randomizeChance(15)){viewDist += viewDist / 2 * (distr(*generator));}
}

bool NeuralParams::randomizeChance(const int percent) {
	return  (rand() % 100 < percent);
}
