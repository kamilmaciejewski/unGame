#ifndef SDLENGINE_H_
#define SDLENGINE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <UNGSettings.h>
#include <UNGWorld.h>
#include <string>
#include <thread>

#include "SDL2_rotozoom.h"
#include "SDLEventHandler.h"
#include "UNGGlobals.h"
#include "UNGLoggingHandler.h"
#include "UNGTimeFrameHandler.hpp"

class SDLEngine {

	UNGTimeFrameHandler timeFrameHandler;
	UNGLogger* logger;
	const std::string ID = "SDL Engine";
	std::thread threadSDL;
	Settings *settings = nullptr;
	bool isRunning = true;
	int frame_counter = 0, frame_counter0 = 0;
	int fps_counter = 0;
	uint32_t fpsTimeDelta, fpsTimeDeltaTemp, msStart, msEnd;
	void drawActiveCreatureInfo(std::string);
	void setEngineParameters();
	void setWindowSize();

	void clearScreen();
//	SDL_bool initTextEngine();
	SDL_bool initSDLEngine();
	void draw();
	void runThread(World*);
	void close();
	uint32_t* countFrameTimeDelta(uint32_t*, uint32_t*);
	TTF_Font *font;

	SDLEventHandler SdlEventHandler;
	SDL_Window *window = nullptr;
//  SDL_Surface* screenSurface = nullptr;
	SDL_Surface *info_surface;
	SDL_Renderer *renderer = nullptr;
	SDL_Texture *info_texture;
	SDL_Color color = { 255, 255, 255 };
	SDL_Rect info_dstrect = { 10, 10, 0, 0 };

public:
	virtual ~SDLEngine();
	SDL_bool init(Settings*);
	void run(World*,Settings *settings);
	void stop();

};
#endif /* SDLENGINE_H_ */
