#include "SDLEventHandler.h"

void SDLEventHandler::handleEvents(bool* result, Settings* settings) {
  while (SDL_PollEvent(&ev) != 0) {
    switch (ev.type) {
    case SDL_QUIT: {
      *result = false;
      break;
    }
    case SDL_KEYDOWN: {
      switch (ev.key.keysym.scancode) {
      case SDL_SCANCODE_V:
        settings->draw_vectors = !settings->draw_vectors;
        break;
      case SDL_SCANCODE_T:
        settings->draw_textures = !settings->draw_textures;
        break;
      case SDL_SCANCODE_R:
             settings->rotate = !settings->rotate;
             break;
      case SDL_SCANCODE_M:
                   settings->move = !settings->move;
                   break;
      case SDL_SCANCODE_ESCAPE:
        *result = false;
        break;
      default:
        break;
      }
      break;
    }
    case SDL_MOUSEMOTION: {
      mousePos.x = ev.motion.x;
      mousePos.y = ev.motion.y;
      break;
    }
    default: {
      break;
    }
    }
  }
}
