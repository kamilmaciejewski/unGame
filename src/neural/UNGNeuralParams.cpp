#include "UNGNeuralParams.h"

NeuralParams::NeuralParams(std::default_random_engine *generator,
			std::normal_distribution<double> *distribution) {
		this->generator = generator;
		this->distribution = distribution;
}

void NeuralParams::randomize() {

		auto distr = *distribution;
		inputSize += inputSize /3 * (distr(*generator));
		hiddenSize += hiddenSize /3 * (distr(*generator));
		outputSize += outputSize /3 * (distr(*generator));
		maxConnections += maxConnections /3 * (distr(*generator));
		fov += fov /3 * (distr(*generator));
		treshold += treshold /3 * (distr(*generator));
	}
