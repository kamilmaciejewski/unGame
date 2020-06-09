#ifndef UNGAME_H_
#define UNGAME_H_

#include "UNGLoggingHandler.h"
#include "MultiEngine.h"
#include "UNGWorldGenerator.h"
#include "UNGEngine.h"
#include "UNGNeuralEngine.h"

class UNGame {
public:
	UNGame(Settings*);
	virtual ~UNGame();
	void run();
	void stop();
private:
	Settings *settings;
	UNGEngine ungEngine;
	SDLEngine sdlEngine;
	UNGNeuralEngine neuralEngine;
	World* world = nullptr;
	UNGLogger* logger;
};

#endif /* UNGAME_H_ */
