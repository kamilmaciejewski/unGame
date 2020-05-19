#ifndef UNGAME_H_
#define UNGAME_H_
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <boost/program_options.hpp>
#include <UNGWorld.h>
#include <UNGWorldGenerator.h>

#include "SDLEngine.h"
#include "UNGConsole.h"
#include "UNGEngine.h"
#include "UNGLoggingHandler.h"
#include "UNGLogger.h"
#include "UNGNeuralEngine.h"

WorldGenerator *worldGenerator;
Settings *settings;
SDL_Surface *screenSurface = nullptr;
SDL_Surface *imageSurface = nullptr;

SDLEngine sdlEngine;
UNGEngine ungEngine;
UNGNeuralEngine neuralEngine;
World *world;
bool handleOptions(int, const char*[]);

#endif /* UNGAME_H_ */
