#ifndef UNG_NEURALENGINE_H_
#define UNG_NEURALENGINE_H_

#include <stdio.h>
#include <UNGSettings.h>
#include <UNGWorld.h>
#include <string>
#include <thread>

#include "SDLEventHandler.h"
#include "UNGGlobals.h"
#include "UNGLoggingHandler.h"
#include "UNGTimeFrameHandler.hpp"

class UNGNeuralEngine {
	UNGLogger *logger = nullptr;
	bool isRunning = true;
	std::thread threadNeur;
	UNGTimeFrameHandler timeFrameHandler;
public:
	UNGNeuralEngine() = default;
	virtual ~UNGNeuralEngine();
	void close();
	void run(World*);
	void runMainThread(World *world);
};

#endif /* UNG_NEURALENGINE_H_ */
