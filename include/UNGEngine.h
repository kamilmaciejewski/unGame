#ifndef SRC_ENGINE_UNGENGINE_H_
#define SRC_ENGINE_UNGENGINE_H_

#include <stdio.h>
#include <string>
#include <thread>

#include "World.h"
#include "SDLEventHandler.h"
#include "Settings.h"
#include "Globals.h"
#include "UNGLoggingHandler.h"
#include "UNGTimeFrameHandler.hpp"

class UNGEngine {
	UNGLogger *logger = nullptr;
	UNGLogger *loggerSenses = nullptr;
	UNGTimeFrameHandler timeFrameHandler;
	UNGTimeFrameHandler timeFrameHandlerSenses;
	bool isFPSLimitEnabled = true;
	int fpsLimit = 99;
	uint32_t frameEnd = 0, frameStart = 0;
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
	uint32_t* countFrameTimeDelta();
};

#endif /* SRC_ENGINE_UNGENGINE_H_ */
