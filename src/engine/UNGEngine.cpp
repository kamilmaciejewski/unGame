#include "UNGEngine.h"

UNGEngine::UNGEngine() {

}

UNGEngine::~UNGEngine() {
}
void UNGEngine::run(World *world) {
	threadWorld = std::thread(&UNGEngine::runMainThread, this, world);
	threadViewSense = std::thread(&UNGEngine::runSensesThread, this, world);
}

void UNGEngine::runMainThread(World *world) {
	std::cout << "UNG engine world running" << std::endl;
	while (isRunning) {
//		countFPS(&frame_res, &msFrameStart, &msFrameEnd, &frame_counter);
		world->update(
				countFrameTimeDelta(&frameTimeDeltaTemp, &frameTimeDelta));
	}
	std::cout << "UNG engine world running stop" << std::endl;
}
void UNGEngine::runSensesThread(World *world) {
	while (isRunning) {
//		countFPS(&sense_res, &msFrameStart0, &msFrameEnd0, &frame_counter0);
		world->updateViewSense();
	}
	std::cout << "Senses thread stopping" << std::endl;
}

void UNGEngine::close() {
	std::cout << "Run stopped, wait for threads close" << std::endl;
	isRunning = false;
	threadWorld.join();
	std::cout<<"World thread stopped"<<std::endl;
	threadViewSense.join();
	std::cout<<"Sense thread stopped"<<std::endl;
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
