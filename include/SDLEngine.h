#ifndef SDLENGINE_H_
#define SDLENGINE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <thread>

#include "SDL2_rotozoom.h"
#include "World.h"
#include "SDLEventHandler.h"
#include "Settings.h"
#include "Globals.h"

class SDLEngine {

	std::thread threadSDL;
	Settings *settings;
	bool isRunning = true;
	int frame_counter = 0, frame_counter0 = 0;
	int fps_counter = 0;
	uint32_t fpsTimeDelta, fpsTimeDeltaTemp, msStart, msEnd;
	void countFPS(std::string*, uint32_t*, uint32_t*, int*);
	void updateFPSInfo();
	void drawActiveCreatureInfo(std::string);
	void setEngineParameters();
	void setWindowSize();

	void clearScreen();
	SDL_bool initTextEngine();
	void draw();
	void runThread(World*);
	void close();
	void log(std::string);
	uint32_t* countFrameTimeDelta(uint32_t*, uint32_t*);

//	std::thread threadWorld;
//	std::thread threadViewSense;
	std::string fps_res, frame_res, sense_res;

	TTF_Font *font;

	SDLEventHandler SdlEventHandler;
	SDL_Window *window = nullptr;
//  SDL_Surface* screenSurface = nullptr;
	SDL_Surface *fps_surface;
	SDL_Surface *info_surface;
	SDL_Renderer *renderer = nullptr;
	SDL_Texture *fps_texture;
	SDL_Texture *info_texture;
	SDL_Color color = { 255, 255, 255 };
	SDL_Rect fps_dstrect = { 10, 10, 0, 0 };
	SDL_Rect info_dstrect = { 10, 30, 0, 0 };

public:
	SDL_bool init(Settings*);
	void run(World*);
	void stop();
	std::queue<std::string> *logger;

};
#endif /* SDLENGINE_H_ */
