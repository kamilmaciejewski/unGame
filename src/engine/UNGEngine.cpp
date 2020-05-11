#include "UNGEngine.h"

UNGEngine::UNGEngine() {

}

UNGEngine::~UNGEngine() {
}
void UNGEngine::run(World *world) {
	logger = LoggingHandler::getLogger("UNG");
	timeFrameHandler.setLogger(logger);
	loggerSenses = LoggingHandler::getLogger("SNS");
	timeFrameHandlerSenses.setLogger(loggerSenses);
	threadWorld = std::thread(&UNGEngine::runMainThread, this, world);
	threadViewSense = std::thread(&UNGEngine::runSensesThread, this, world);
}

void UNGEngine::runMainThread(World *world) {
	logger->log("world running");
	while (isRunning) {
		world->update(
				countFrameTimeDelta());
		timeFrameHandler.frameTick();
	}
	logger->log("world running stop");
}
void UNGEngine::runSensesThread(World *world) {
	while (isRunning) {
//		countFPS(&sense_res, &msFrameStart0, &msFrameEnd0, &frame_counter0);
		world->updateViewSense();
		timeFrameHandlerSenses.frameTick();
	}
	logger->log("Senses thread stopping");
}

void UNGEngine::close() {
	logger->log("Run stopped, wait for threads close");
	isRunning = false;
	threadWorld.join();
	logger->log("World thread stopped");
	threadViewSense.join();
	logger->log("Sense thread stopped");
}

uint32_t* UNGEngine::countFrameTimeDelta() {
	frameTimeDeltaTemp = SDL_GetTicks() - frameTimeDelta;
	if (isFPSLimitEnabled && frameTimeDeltaTemp < (1000.0 / fpsLimit)) {
		SDL_Delay(1);
		return (countFrameTimeDelta());
	} else {
		frameTimeDelta = SDL_GetTicks();
		return (&frameTimeDeltaTemp);
	}
}
