#ifndef SDLEVENTHANDLER_H_
#define SDLEVENTHANDLER_H_

#include <SDL2/SDL.h>
#include <iostream>
#include "Settings.h"

class SDLEventHandler {
  SDL_Event ev;

public:
  void handleEvents(bool*, Settings*);
  SDL_Point mousePos;
};
#endif /* SDLEVENTHANDLER_H_ */
