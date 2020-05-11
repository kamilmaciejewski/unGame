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

//TODO: not used
//uint32_t* countFrameTimeDelta(uint32_t *fTimeDeltaTemp,
//		uint32_t *fTimeDelta) {
//	*fTimeDeltaTemp = SDL_GetTicks() - *fTimeDelta;
//	if (isFPSLimitEnabled && *fTimeDeltaTemp < (1000.0 / fpsLimit)) {
//		SDL_Delay(1);
//		return (countFrameTimeDelta(fTimeDeltaTemp, fTimeDelta));
//	} else {
//		*fTimeDelta = SDL_GetTicks();
//		return (&frameTimeDeltaTemp);
//		return fTimeDeltaTemp;
//	}
//}
