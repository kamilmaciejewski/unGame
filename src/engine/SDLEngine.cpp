#include <iostream>

#include "SDLEngine.h"

bool SDLEngine::init() {

  if (SDL_Init( SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return (false);
  } else {
    setWindowSize();
    setEngineParameters();
    window = SDL_CreateWindow("unGame", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (window == nullptr) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      return (false);
    } else {
      screenSurface = SDL_GetWindowSurface(window);
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (renderer == nullptr) {
      return (false);

    }
    frameTimeDelta = SDL_GetTicks();
    return (true);
  }
}
void SDLEngine::run(World * world) {
  while (isRunning) {
    SdlEventHandler.handleEvents(&isRunning);
    SDL_RenderClear(renderer);
    world->updateAndDraw(countFrameTimeDelta(), renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_RenderPresent(renderer);
    countFPS();
  }
}

void SDLEngine::close() {
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  window = nullptr;
  renderer = nullptr;
  SDL_Quit();
}

void SDLEngine::countFPS() {
  msEnd = SDL_GetTicks();
  if ((msEnd - msStart) > 1000) {
    msStart = SDL_GetTicks();
    std::cout << "FPS: " << frame_counter << std::endl;
    frame_counter = 0;
  } else {
    ++frame_counter;
  }
}

uint32_t SDLEngine::countFrameTimeDelta() {
  frameTimeDeltaTemp = SDL_GetTicks() - frameTimeDelta;
  if (isFPSLimitEnabled && frameTimeDeltaTemp < (1000.0 / fpsLimit)) {
    SDL_Delay(1);
    return (countFrameTimeDelta());
  } else {
    frameTimeDelta = SDL_GetTicks();
    return (frameTimeDeltaTemp);
  }
}

void SDLEngine::setEngineParameters() {
  SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1"); //smoothing
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

}

void SDLEngine::setWindowSize() {
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);
  SCREEN_WIDTH = DM.w;
  SCREEN_HEIGHT = DM.h;
}
