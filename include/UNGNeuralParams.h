#ifndef UNGNEURALPARAMS_H_
#define UNGNEURALPARAMS_H_

#include <random>
#include <UNGLoggingHandler.h>

class NeuralParams {
public:

	NeuralParams(std::default_random_engine*,
			std::normal_distribution<double>*);

	std::normal_distribution<double> *distribution;
	std::default_random_engine *generator;
	uint8_t inputSize = 20;
	uint8_t hiddenSize = 50;
	uint8_t outputSize = 10;
	uint8_t maxConnections = 10;
	uint16_t neuronFov = 45;
	uint16_t sightFov = 135;
	float treshold = 0.2;

	float speed = 0.04;
	float rotationFactor = 0.04;
	float speedFactor = 0.0015;
	uint16_t viewDist = 300;
	void randomize();
	float randomizeVal(float);
	bool randomizeChance(const int percent);

};

#endif /* UNGNEURALPARAMS_H_ */
