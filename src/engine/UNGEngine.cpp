#include "UNGEngine.h"

UNGEngine::~UNGEngine() {
}
void UNGEngine::run(World *world) {
	SDL_Init(SDL_INIT_TIMER);
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
		world->update(countFrameTimeDelta());
		timeFrameHandler.frameTick();
	}
	logger->log("world running stop");
}
void UNGEngine::runSensesThread(World *world) {
	while (isRunning) {
		world->updateViewSense();
		timeFrameHandlerSenses.frameTick();
	}
	logger->log("Senses thread stopping");
}

void UNGEngine::close() {

	if (SDL_WasInit(SDL_INIT_TIMER)) {
		SDL_QuitSubSystem(SDL_INIT_TIMER);
	}
	logger->log("Run stopped, wait for threads close");
	isRunning = false;
	threadWorld.join();
	logger->log("World thread stopped");
	threadViewSense.join();
	logger->log("Sense thread stopped");
}

uint32_t* UNGEngine::countFrameTimeDelta() {
	frameStart = SDL_GetTicks() - frameEnd;
	if (isFPSLimitEnabled && frameStart < (1000.0 / fpsLimit)) {
		SDL_Delay(1);
		return (countFrameTimeDelta());
	} else {
	frameEnd = SDL_GetTicks();
	return (&frameStart);
	}
}
