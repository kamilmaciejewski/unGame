#ifndef UNGAME_TIMEFRAMEHANDLER_HPP_
#define UNGAME_TIMEFRAMEHANDLER_HPP_

#include <SDL2/SDL.h>
#include "UNGLogger.h"

class UNGTimeFrameHandler {
	uint32_t frameEnd = 0, frameStart = 0, frameCounter = 0;
	UNGLogger *logger;
public:
	void frameTick();
	bool isFPSLimitEnabled = true;
	uint32_t fpsLimit = 30;
	uint32_t fpsLimitDelta = 1000.0/fpsLimit;
	void setLogger(UNGLogger*);
	virtual ~UNGTimeFrameHandler();
};

#endif /* UNGAME_TIMEFRAMEHANDLER_HPP_ */
