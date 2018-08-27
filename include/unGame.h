#ifndef UNGAME_H_
#define UNGAME_H_
#include "World.h"
#include "WorldGenerator.h"
#include "SDLEngine.h"

WorldGenerator * worldGenerator;
Settings* settings;
SDL_Surface* screenSurface = nullptr;
SDL_Surface* imageSurface = nullptr;

SDLEngine engine;
World * world;

#endif /* UNGAME_H_ */
