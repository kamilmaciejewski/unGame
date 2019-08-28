#include <iostream>

#include "SDLEngine.h"

void SDLEngine::runThread(World* world) {
  while (isRunning) {
    countFPS(&frame_res, &msFrameStart, &msFrameEnd, &frame_counter);
    world->update(countFrameTimeDelta(&frameTimeDeltaTemp, &frameTimeDelta));
  }
}

bool SDLEngine::init(Settings* settings) {
  this->settings = settings;
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
//        | SDL_RENDERER_PRESENTVSYNC //vsync - don't draw more than screen refresh
        );
    SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
    if (renderer == nullptr) {
      return (false);

    }
    initTextEngine();
    return (true);
  }
}
void SDLEngine::run(World* world) {
  thread2 = std::thread(&SDLEngine::runThread, this, world);
  while (isRunning) {
    SdlEventHandler.handleEvents(&isRunning, settings);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    world->markActiveObjectByMousePos(SdlEventHandler.mousePos);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
    world->draw(renderer, &screenWidth, &screenHeight);
    updateFPSInfo();
    SDL_RenderCopy(renderer, fps_texture, nullptr, &fps_dstrect);
    SDL_RenderPresent(renderer);
    countFrameTimeDelta(&fpsTimeDelta, &fpsTimeDeltaTemp);
    countFPS(&fps_res, &msStart, &msEnd, &fps_counter);
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

void SDLEngine::countFPS(std::string* res_string, uint32_t* msStart,
    uint32_t* msEnd, int* frame_counter) {
  *msEnd = SDL_GetTicks();
  if (*msEnd - *msStart > 1000) {
    *msStart = SDL_GetTicks();
    *res_string = std::to_string(*frame_counter);
    *frame_counter = 0;
  } else {
    ++*frame_counter;
  }
}

void SDLEngine::updateFPSInfo() {
  std::string asd = "Draw FPS: " + fps_res + " Engine FPS: " + frame_res;
  fps_surface = TTF_RenderText_Solid(font, asd.c_str(), color);
  fps_texture = SDL_CreateTextureFromSurface(renderer, fps_surface);
  SDL_QueryTexture(fps_texture, nullptr, nullptr, &fps_dstrect.w,
      &fps_dstrect.h);
}

uint32_t* SDLEngine::countFrameTimeDelta(uint32_t* fTimeDeltaTemp,
    uint32_t* fTimeDelta) {
  *fTimeDeltaTemp = SDL_GetTicks() - *fTimeDelta;
  if (isFPSLimitEnabled && *fTimeDeltaTemp < (1000.0 / fpsLimit)) {
    SDL_Delay(1);
    return (countFrameTimeDelta(fTimeDeltaTemp, fTimeDelta));
  } else {
    *fTimeDelta = SDL_GetTicks();
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

void SDLEngine::initTextEngine() {
  if (TTF_Init() != 0) {
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
