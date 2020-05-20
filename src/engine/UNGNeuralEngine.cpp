#include "UNGNeuralEngine.h"

UNGNeuralEngine::~UNGNeuralEngine() {
}
void UNGNeuralEngine::run(World *world) {
	logger = LoggingHandler::getLogger("NEUR");
	timeFrameHandler.setLogger(logger);
	threadNeur = std::thread(&UNGNeuralEngine::runMainThread, this, world);
}

void UNGNeuralEngine::runMainThread(World *world) {
	logger->log("engine running");

	while (isRunning) {
		world->updateNeuralNetworks();
		timeFrameHandler.frameTick();
	}
	logger->log("engine stop");
}

void UNGNeuralEngine::close() {

	logger->log("engine stopped, wait for threads close");
	isRunning = false;
	threadNeur.join();
	logger->log("Thread stopped");
}

