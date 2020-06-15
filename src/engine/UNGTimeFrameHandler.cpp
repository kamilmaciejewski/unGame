#include <UNGTimeFrameHandler.hpp>
#include <thread>
#include <chrono>

void UNGTimeFrameHandler::setLogger(UNGLogger *logger_) {
	logger = logger_;
}

void UNGTimeFrameHandler::frameTick() {

	if (isFPSLimitEnabled) {
		while (SDL_GetTicks() - frameStart < fpsLimitDelta) {
//			std::this_thread::sleep_for(std::chrono::milliseconds(fpsLimitDelta / (SDL_GetTicks() - frameStart + 1) / 2));
			std::this_thread::sleep_for(std::chrono::milliseconds(2));
//			SDL_Delay(fpsLimitDelta / (SDL_GetTicks() - frameStart + 1) / 2);
//			SDL_Delay(1);
		}
	}
	frameStart = SDL_GetTicks();
	if (SDL_GetTicks() - frameEnd > 1000) {
		frameEnd = SDL_GetTicks();
		logger->reportFps(frameCounter);
		frameCounter = 0;
	} else {
		++frameCounter;
	}
}
UNGTimeFrameHandler::~UNGTimeFrameHandler() {
	logger = nullptr;
}
