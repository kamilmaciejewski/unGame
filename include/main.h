#ifndef MAIN_H_
#define MAIN_H_
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
#include "MultiEngine.h"
#include "UNGame.h"

WorldGenerator *worldGenerator;
Settings *settings;
SDL_Surface *screenSurface = nullptr;
SDL_Surface *imageSurface = nullptr;

//SDLEngine sdlEngine;
//UNGEngine ungEngine;
//UNGNeuralEngine neuralEngine;
World *world;
bool handleOptions(int, const char*[]);

#endif /* MAIN_H_ */
