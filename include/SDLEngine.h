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

	Settings *settings;
	bool isRunning = true;
		bool isFPSLimitEnabled = false;
		int fpsLimit = 99;
		int frame_counter = 0, frame_counter0 = 0;
		int fps_counter = 0;
 		uint32_t fpsTimeDelta, fpsTimeDeltaTemp, frameTimeDelta, frameTimeDeltaTemp,
				msFrameStart, msFrameStart0, msFrameEnd, msFrameEnd0, msStart,
				msEnd;

	void countFPS(std::string*, uint32_t*, uint32_t*, int*);
	void updateFPSInfo();
	void drawActiveCreatureInfo(std::string);
	void setEngineParameters();
	void setWindowSize();
	void runMainThread(World *world);
	void runSensesThread(World *world);
	void clearScreen();
	SDL_bool initTextEngine();


	uint32_t* countFrameTimeDelta(uint32_t*, uint32_t*);

	std::thread threadWorld;
	std::thread threadViewSense;
	std::string fps_res, frame_res, sense_res;

	TTF_Font *font;

	SDLEventHandler SdlEventHandler;
	SDL_Window *window = nullptr;
//  SDL_Surface* screenSurface = nullptr;
	SDL_Surface *fps_surface;
	SDL_Surface *info_surface;
	SDL_Renderer *renderer = nullptr;
	SDL_Texture *tex = nullptr;
	SDL_Texture *fps_texture;
	SDL_Texture *info_texture;
	SDL_Color color = { 255, 255, 255 };
	SDL_Rect fps_dstrect = { 10, 10, 0, 0 };
	SDL_Rect info_dstrect = { 10, 30, 0, 0 };

public:
	SDL_bool init(Settings*);
	void close();
	void draw();
	void run(World*);
	void run();
	//simple mode
	void init();
};

#endif /* SDLENGINE_H_ */
