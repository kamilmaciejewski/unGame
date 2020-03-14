#include <SDL2/SDL.h>
#include <cmath>

#include "FPSHandler.hpp"

uint32_t* countFrameTimeDelta(uint32_t *fTimeDeltaTemp,
		uint32_t *fTimeDelta) {
	*fTimeDeltaTemp = SDL_GetTicks() - *fTimeDelta;
//	if (isFPSLimitEnabled && *fTimeDeltaTemp < (1000.0 / fpsLimit)) {
//		SDL_Delay(1);
//		return (countFrameTimeDelta(fTimeDeltaTemp, fTimeDelta));
//	} else {
		*fTimeDelta = SDL_GetTicks();
//		return (&frameTimeDeltaTemp);
		return fTimeDeltaTemp;
//	}
}
