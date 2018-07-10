#include <iostream>

#include "SDLEngine.h"

void SDLEngine::runThread(World* world) {
  while (isRunning) {
    world->update(countFrameTimeDelta());
  }
}

bool SDLEngine::init() {

  if (SDL_Init( SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    return (false);
  } else {
    setWindowSize();
    window = SDL_CreateWindow("unGame", SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight,
        SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (window == nullptr) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      return (false);
    } else {
      screenSurface = SDL_GetWindowSurface(window);
    }
    setEngineParameters();
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED
//        | SDL_RENDERER_PRESENTVSYNC
        );
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
    if (renderer == nullptr) {
      return (false);

    }
    initTextEngine();//    frameTimeDelta = SDL_GetTicks();
    return (true);
  }
}
void SDLEngine::run(World* world) {
  thread2 = std::thread(&SDLEngine::runThread, this, world);
  while (isRunning) {
    SdlEventHandler.handleEvents(&isRunning);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    world->checkPos(SdlEventHandler.mousePos);
    world->draw(renderer, &screenWidth, &screenHeight);
    SDL_RenderCopy(renderer, fps_texture, NULL, &fps_dstrect);
    SDL_RenderPresent(renderer);
    countFPS();
  }
}

void SDLEngine::close() {
  thread2.join();
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  window = nullptr;
  renderer = nullptr;
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_Quit();
}

void SDLEngine::countFPS() {
  msEnd = SDL_GetTicks();
  if (msEnd - msStart > 1000) {
    msStart = SDL_GetTicks();
    fps_res = "FPS: " +std::to_string(frame_counter);
    fps_surface = TTF_RenderText_Solid(font,fps_res.c_str(), color);
    fps_texture = SDL_CreateTextureFromSurface(renderer, fps_surface);
    SDL_QueryTexture(fps_texture, NULL, NULL, &texW, &texH);
    fps_dstrect = { 10, 10, texW, texH };
;
    frame_counter = 0;
  } else {
    ++frame_counter;
  }
}

uint32_t* SDLEngine::countFrameTimeDelta() {
  frameTimeDeltaTemp = SDL_GetTicks() - frameTimeDelta;
  if (isFPSLimitEnabled && frameTimeDeltaTemp < (1000.0 / fpsLimit)) {
    SDL_Delay(1);
    return (countFrameTimeDelta());
  } else {
    frameTimeDelta = SDL_GetTicks();
    return (&frameTimeDeltaTemp);
  }
}

void SDLEngine::setEngineParameters() {
  SDL_GL_SetSwapInterval(1);
  SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, ""); //smoothing
  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

}

void SDLEngine::initTextEngine(){
  if (TTF_Init() != 0){
    printf("TTF_Init failed");
    SDL_Quit();
  }
  font = TTF_OpenFont("res/Pixel.ttf", 15);

}

void SDLEngine::setWindowSize() {
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);
  screenWidth = DM.w;
  screenHeight = DM.h;
}
