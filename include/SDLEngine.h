 *
#ifndef SDLENGINE_H_
#define SDLENGINE_H_

#include <SDL2/SDL.h>
#include <stdio.h>

#include "SDL2_rotozoom.h"
#include "World.h"
#include "SDLEventHandler.h"
#include "Constants.h"

class SDLEngine {
  SDLEventHandler SdlEventHandler;
  bool isRunning = true;
  bool isFPSLimitEnabled = false;
  int fpsLimit = 200;
  int frame_counter = 0;

  SDL_Window* window = nullptr;
  SDL_Surface* screenSurface = nullptr;
  uint32_t frameTimeDelta, frameTimeDeltaTemp, msStart, msEnd;
  void countFPS();
  uint32_t countFrameTimeDelta();

public:
  bool init();
  void close();
  void run(World *);
};

#endif /* SDLENGINE_H_ */
