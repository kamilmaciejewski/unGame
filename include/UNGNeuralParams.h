#ifndef UNGNEURALPARAMS_H_
#define UNGNEURALPARAMS_H_

#include <random>
#include <UNGLoggingHandler.h>

class NeuralParams {
public:

	NeuralParams(std::default_random_engine*, std::normal_distribution<double>*);

	std::normal_distribution<double> *distribution;
	std::default_random_engine *generator;
	uint8_t inputSize = 10;
	uint8_t hiddenSize = 30;
	uint8_t outputSize = 10;
	uint8_t maxConnections = 10;
	uint8_t fov = 45;
	double treshold = 0.2;
	void randomize();
};

#endif /* UNGNEURALPARAMS_H_ */
