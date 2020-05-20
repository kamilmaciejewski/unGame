#include <UNGTimeFrameHandler.hpp>

void UNGTimeFrameHandler::setLogger(UNGLogger *logger_) {
	logger = logger_;
}

void UNGTimeFrameHandler::frameTick() {

	frameStart = SDL_GetTicks();
	if (isFPSLimitEnabled) {
		while (SDL_GetTicks() - frameStart < fpsLimitDelta) {
//			SDL_Delay(fpsLimitDelta / (SDL_GetTicks() - frameStart + 1) / 10);
			SDL_Delay(1);
		}
	}
	if (SDL_GetTicks() - frameEnd > 1000) {
		frameEnd = SDL_GetTicks();
		logger->reportFps(frameCounter);
		frameCounter = 0;
	} else {
		++frameCounter;
	}
}
