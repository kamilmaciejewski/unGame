#ifndef UNGAME_TIMEFRAMEHANDLER_HPP_
#define UNGAME_TIMEFRAMEHANDLER_HPP_

#include <SDL2/SDL.h>
#include "UNGLogger.h"

class UNGTimeFrameHandler {
	uint32_t msStart = 0, msEnd = 0, frameCounter = 0;
	UNGLogger *logger;
public:
	void frameTick();
	bool isFPSLimitEnabled = true;
	int fpsLimit = 99;
	void setLogger(UNGLogger*);
};

#endif /* UNGAME_TIMEFRAMEHANDLER_HPP_ */
