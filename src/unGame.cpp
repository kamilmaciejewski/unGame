//#include <SDL.h>
//
//int main(int argc, char* argv[]) {
//    // Start SDL2
//    SDL_Init(SDL_INIT_EVERYTHING);
//
//    // Create a Window in the middle of the screen
//    SDL_Window *window = 0;
//
//    window = SDL_CreateWindow("Hello World!",
//                              SDL_WINDOWPOS_CENTERED,
//                              SDL_WINDOWPOS_CENTERED,
//                              640, 480,
//                              SDL_WINDOW_SHOWN);
//
//    // Delay so that we can see the window appear
//    for (int i=0;i<99;i++){
//    SDL_Delay(2000);
//    }
//
//    // Cleanup and Quit
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//}
//Using SDL and standard IO
/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
 and may not be redistributed without written permission.*/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

#include "rotozoom/SDL2_rotozoom.h"
#include "include/unGame.h"
#include "engine/SDLEngine.h"

int main(int argc, char* args[]) {
    SDLEngine engine;
    engine.init();
    engine.run(world);
    engine.close();
//    SDL_Rect rectPos { 200, 200, 0, 0 };
//    SDL_Rect rectCut { 0, 0, 300, 300 };

//    int rot = 80;
//    float x = 0;
//    float y = 0;
//
//        rot += 1;
//        if (rot > 360) {
//            rot -= 360;
//        }
//        SDL_FillRect(screenSurface, NULL, 0);
//        SDL_Surface *rotSurface = rotozoomSurface(imageSurface, rot, 1, 0);
//        x += sin(rot * M_PI / 180) * 2.0;
//        y += cos(rot * M_PI / 180) * 2.0;
//        SDL_Rect rec { int(x), int(y), 0, 0 };
//        rec.x -= rotSurface->w / 2 - imageSurface->w / 2;
//        rec.y -= rotSurface->h / 2 - imageSurface->h / 2;
//
//        SDL_BlitSurface(rotSurface, NULL, screenSurface, &rec);
    return 0;
}
