#ifndef SDLEVENTHANDLER_H_
#define SDLEVENTHANDLER_H_

#include <SDL2/SDL.h>
#include <iostream>

class SDLEventHandler {
  SDL_Event ev;

public:
  void handleEvents(bool*);
  SDL_Point mousePos;
};
#endif /* SDLEVENTHANDLER_H_ */
