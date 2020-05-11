#ifndef UNGAME_TIMEFRAMEHANDLER_HPP_
#define UNGAME_TIMEFRAMEHANDLER_HPP_

#include <SDL2/SDL.h>
#include "UNGLogger.h"

class UNGTimeFrameHandler {
	uint32_t msStart, msEnd, frameCounter;
	UNGLogger* logger;
	public:
	void frameTick();
	void setLogger(UNGLogger*);
};

#endif /* UNGAME_TIMEFRAMEHANDLER_HPP_ */
