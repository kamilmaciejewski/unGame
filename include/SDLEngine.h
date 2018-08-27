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
#include "Settings.h"

class SDLEngine {
  void countFPS(std::string*, uint32_t*, uint32_t*, int*);
  void updateFPSInfo();
  void setEngineParameters();
  void setWindowSize();
  void runThread(World* world);
  void initTextEngine();

  Settings* settings;
  bool isRunning = true;
  bool isFPSLimitEnabled = false;
  int fpsLimit = 99;
  int frame_counter = 0;
  int fps_counter = 0;
  int screenWidth = 0;
  int screenHeight = 0;
  uint32_t fpsTimeDelta, fpsTimeDeltaTemp, frameTimeDelta, frameTimeDeltaTemp,
      msFrameStart, msFrameEnd, msStart, msEnd;
  uint32_t* countFrameTimeDelta(uint32_t*, uint32_t*);

  std::thread thread2;
  std::string fps_res, frame_res;

  TTF_Font * font;

  SDLEventHandler SdlEventHandler;
  SDL_Window* window = nullptr;
  SDL_Surface* screenSurface = nullptr;
  SDL_Surface * fps_surface;
  SDL_Renderer* renderer = nullptr;
  SDL_Texture * fps_texture;
  SDL_Color color = { 255, 255, 255 };
  SDL_Rect fps_dstrect = { 10, 10, 0, 0 };

public:
  bool init(Settings*);
  void close();
  void run(World *);
};

#endif /* SDLENGINE_H_ */
