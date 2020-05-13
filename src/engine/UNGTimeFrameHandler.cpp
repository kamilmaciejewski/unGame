#include <UNGTimeFrameHandler.hpp>

void UNGTimeFrameHandler::setLogger(UNGLogger* logger_) {
	logger = logger_;
}

void UNGTimeFrameHandler::frameTick(){
		msEnd = SDL_GetTicks();
		if (msEnd - msStart > 1000) {
			msStart = SDL_GetTicks();
			logger->reportFps(frameCounter);
			frameCounter = 0;
		} else {
			++frameCounter;
		}
}
