#ifndef SRC_ENGINE_UNGENGINE_H_
#define SRC_ENGINE_UNGENGINE_H_

#include <stdio.h>
#include <string>
#include <thread>

#include "World.h"
#include "SDLEventHandler.h"
#include "Settings.h"
#include "Globals.h"
class UNGEngine {
	bool isFPSLimitEnabled = false;
	int fpsLimit = 99;
	uint32_t frameTimeDelta, frameTimeDeltaTemp,
			msFrameStart, msFrameStart0, msFrameEnd, msFrameEnd0;
	bool isRunning = true;
	std::thread threadWorld;
	std::thread threadViewSense;
public:
	UNGEngine();
	virtual ~UNGEngine();
	void close();
	void run(World*);
	void runMainThread(World *world);
	void runSensesThread(World *world);
	uint32_t* countFrameTimeDelta(uint32_t*, uint32_t*);
};

#endif /* SRC_ENGINE_UNGENGINE_H_ */
