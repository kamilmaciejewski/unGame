#include "UNGEngine.h"

UNGEngine::UNGEngine() {

}

UNGEngine::~UNGEngine() {
}
void UNGEngine::run(World *world) {
	logger = LoggingHandler::getLogger("UNG Engine");
	logger->reportFps(9);
	threadWorld = std::thread(&UNGEngine::runMainThread, this, world);
	threadViewSense = std::thread(&UNGEngine::runSensesThread, this, world);
}

void UNGEngine::runMainThread(World *world) {
	logger->log("world running");
	while (isRunning) {
//		countFPS(&frame_res, &msFrameStart, &msFrameEnd, &frame_counter);
		world->update(
				countFrameTimeDelta(&frameTimeDeltaTemp, &frameTimeDelta));
	}
	logger->log("world running stop");
}
void UNGEngine::runSensesThread(World *world) {
	while (isRunning) {
//		countFPS(&sense_res, &msFrameStart0, &msFrameEnd0, &frame_counter0);
		world->updateViewSense();
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

uint32_t* UNGEngine::countFrameTimeDelta(uint32_t *fTimeDeltaTemp,
		uint32_t *fTimeDelta) {
	*fTimeDeltaTemp = SDL_GetTicks() - *fTimeDelta;
	if (isFPSLimitEnabled && *fTimeDeltaTemp < (1000.0 / fpsLimit)) {
		SDL_Delay(1);
		return (countFrameTimeDelta(fTimeDeltaTemp, fTimeDelta));
	} else {
		*fTimeDelta = SDL_GetTicks();
		return (fTimeDeltaTemp);
	}
}
