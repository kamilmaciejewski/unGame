#ifndef SDLEVENTHANDLER_H_
#define SDLEVENTHANDLER_H_

#include <SDL2/SDL.h>

class SDLEventHandler {
  SDL_Event ev;

public:
  void handleEvents(bool*);
};

#endif /* SDLEVENTHANDLER_H_ */
