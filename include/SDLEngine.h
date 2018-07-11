#ifndef SDLENGINE_H_
#define SDLENGINE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>

#include "mingw.thread.h"
#include "SDL2_rotozoom.h"
#include "World.h"
#include "SDLEventHandler.h"

class SDLEngine {
  SDLEventHandler SdlEventHandler;
  bool isRunning = true;
  bool isFPSLimitEnabled = true;
  int fpsLimit = 99;
  int frame_counter = 0;
  int fps_counter = 0;

  SDL_Window* window = nullptr;
  SDL_Surface* screenSurface = nullptr;
  SDL_Renderer* renderer = nullptr;
  uint32_t fpsTimeDelta, fpsTimeDeltaTemp, frameTimeDelta, frameTimeDeltaTemp,msFrameStart, msFrameEnd, msStart, msEnd;
  void countFPS(std::string*, uint32_t*, uint32_t*, int*);
  uint32_t* countFrameTimeDelta(uint32_t*, uint32_t*);
  void setEngineParameters();
  void setWindowSize();
  int screenWidth = 0;
  int screenHeight = 0;
  void runThread(World* world);
  std::thread thread2;
  TTF_Font * font;
  void initTextEngine();
  SDL_Color color = { 255, 255, 255 };
  int texW = 0;
  int texH = 0;
  std::string fps_res, frame_res;
  SDL_Surface * fps_surface;
  SDL_Texture * fps_texture;
  SDL_Rect fps_dstrect;


public:
  bool init();
  void close();
  void run(World *);
};

#endif /* SDLENGINE_H_ */
