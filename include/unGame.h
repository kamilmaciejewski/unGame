#ifndef UNGAME_H_
#define UNGAME_H_
#include "World.h"
#include "WorldGenerator.h"
#include "SDLEngine.h"
#include "UNGEngine.h"
#include "UNGConsole.h"
#include "UNGLoggingHandler.h"

WorldGenerator *worldGenerator;
Settings *settings;
SDL_Surface *screenSurface = nullptr;
SDL_Surface *imageSurface = nullptr;

SDLEngine sdlEngine;
UNGEngine ungEngine;
World *world;

#endif /* UNGAME_H_ */
