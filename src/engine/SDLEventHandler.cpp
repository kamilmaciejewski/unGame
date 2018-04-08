#include "SDLEventHandler.h"

void SDLEventHandler::handleEvents(bool* result) {
  while (SDL_PollEvent(&ev) != 0) {
    switch (ev.type) {
    case SDL_QUIT: {
      *result = false;
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

