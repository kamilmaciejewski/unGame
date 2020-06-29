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
	uint16_t inputSize = 50;
	uint16_t hiddenSize = 50;
//	float sightSharpness = 2.0/inputSize;
	float sightSharpness = 0.15;
	uint8_t outputSize = 10;
	uint8_t maxConnections = 10;
	float maxConnectionDistance = 300;
	float connWeightAngleFactor = 0.0;
	uint16_t neuronFov = 45;
	uint16_t sightFov = 145;
	float treshold = 0.3;

	float speed = 0.06;
	float rotationFactor = 0.06;
	float speedFactor = 0.001;
	float feedDetectspeedFactor = 0.2;
	float viewDist = 300;
	int connectionCopyChance = 90;
	void randomize();
	float randomizeVal(float);
	bool randomizeChance(const int percent);

};

#endif /* UNGNEURALPARAMS_H_ */
