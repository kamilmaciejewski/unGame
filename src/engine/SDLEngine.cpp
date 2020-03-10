#include <iostream>

#include "SDLEngine.h"

void SDLEngine::runMainThread(World *world) {
	while (isRunning) {
		countFPS(&frame_res, &msFrameStart, &msFrameEnd, &frame_counter);
		world->update(
				countFrameTimeDelta(&frameTimeDeltaTemp, &frameTimeDelta));
	}
	std::cout<<"World thread stopping"<<std::endl;
}
void SDLEngine::runSensesThread(World *world) {
	while (isRunning) {
		countFPS(&sense_res, &msFrameStart0, &msFrameEnd0, &frame_counter0);
		world->updateViewSense();
	}
	std::cout<<"Senses thread stopping"<<std::endl;
}

void SDLEngine::init() {
	if (SDL_Init( SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	setWindowSize();
	window = SDL_CreateWindow("unGame", SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, UNG_Globals::SCREEN_W, UNG_Globals::SCREEN_H,
			SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}

	renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC //vsync - don't draw more than screen refresh
					);
	SDL_RenderSetLogicalSize(renderer, UNG_Globals::SCREEN_W,
			UNG_Globals::SCREEN_H);

	if (renderer == nullptr) {
		SDL_DestroyWindow(window);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError()
				<< std::endl;
		SDL_Quit();
	}
}
SDL_bool SDLEngine::init(Settings *settings) {
	this->settings = settings;
	if (SDL_Init( SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return SDL_FALSE;
	} else {
		setWindowSize();
		window = SDL_CreateWindow("unGame", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, UNG_Globals::SCREEN_W, UNG_Globals::SCREEN_H,
//				SDL_WINDOW_FULLSCREEN_DESKTOP
				SDL_WINDOW_SHOWN);

		if (window == nullptr) {
			printf("Window could not be created! SDL_Error: %s\n",
					SDL_GetError());
			return SDL_FALSE;
		} else {
//      screenSurface = SDL_GetWindowSurface(window); is it needed?
		}
		setEngineParameters();
		renderer = SDL_CreateRenderer(window, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC //vsync - don't draw more than screen refresh
						);
		SDL_RenderSetLogicalSize(renderer, UNG_Globals::SCREEN_W,
				UNG_Globals::SCREEN_H);
		if (renderer == nullptr) {
			return SDL_FALSE;
		}
		return initTextEngine();
	}
}
void SDLEngine::run() {
	std::string imagePath = "res/hello.bmp";
	SDL_Surface *bmp = SDL_LoadBMP(imagePath.c_str());
	if (bmp == nullptr) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}
	tex = SDL_CreateTextureFromSurface(renderer, bmp);
	SDL_FreeSurface(bmp);
	if (tex == nullptr) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError()
				<< std::endl;
		SDL_Quit();
	}
	while (isRunning) {
		SdlEventHandler.handleEvents(&isRunning, settings);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, tex, NULL, NULL);
		SDL_RenderPresent(renderer);
	}
}
void SDLEngine::run(World *world) {
	threadWorld = std::thread(&SDLEngine::runMainThread, this, world);
	threadViewSense = std::thread(&SDLEngine::runSensesThread, this, world);
	while (isRunning) {
		SdlEventHandler.handleEvents(&isRunning, settings);
		clearScreen();
		world->markActiveObjectByMousePos(SdlEventHandler.mousePos);
		world->draw(renderer);
		updateFPSInfo();
		drawActiveCreatureInfo(world->infoStr);
		draw();
		countFrameTimeDelta(&fpsTimeDelta, &fpsTimeDeltaTemp);
		countFPS(&fps_res, &msStart, &msEnd, &fps_counter);
	}
	std::cout<<"Run stopped, wait for threads close"<<std::endl;
	threadWorld.join();
	std::cout<<"World thread stopped"<<std::endl;
	threadViewSense.join();
	std::cout<<"Sense thread stopped"<<std::endl;
}
void SDLEngine::clearScreen() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}
void SDLEngine::draw() {
	SDL_RenderCopy(renderer, fps_texture, nullptr, &fps_dstrect);
	SDL_RenderCopy(renderer, info_texture, nullptr, &info_dstrect);
	SDL_RenderPresent(renderer);
}

void SDLEngine::close() {
	threadWorld.join();
	threadViewSense.join();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = nullptr;
	renderer = nullptr;
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}

void SDLEngine::countFPS(std::string *res_string, uint32_t *msStart,
		uint32_t *msEnd, int *frame_counter) {
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
	std::string asd = "Draw FPS: " + fps_res + " Engine FPS: " + frame_res
			+ " Sense FPS: " + sense_res;
	fps_surface = TTF_RenderText_Solid(font, asd.c_str(), color);
	fps_texture = SDL_CreateTextureFromSurface(renderer, fps_surface);
	SDL_QueryTexture(fps_texture, nullptr, nullptr, &fps_dstrect.w,
			&fps_dstrect.h);
	SDL_FreeSurface(fps_surface);
}
void SDLEngine::drawActiveCreatureInfo(std::string infoStr) {
	info_surface = TTF_RenderText_Solid(font, infoStr.c_str(), color);
	info_texture = SDL_CreateTextureFromSurface(renderer, info_surface);
	SDL_QueryTexture(info_texture, nullptr, nullptr, &info_dstrect.w,
			&info_dstrect.h);
	SDL_FreeSurface(info_surface);
}

uint32_t* SDLEngine::countFrameTimeDelta(uint32_t *fTimeDeltaTemp,
		uint32_t *fTimeDelta) {
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
//  SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, ""); //smoothing
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
//    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
//    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
//    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

}

SDL_bool SDLEngine::initTextEngine() {
	if (TTF_Init() != 0) {
		std::cout << "TTF_Init failed" << std::endl;
		SDL_Quit();
		return SDL_FALSE;
	}
	font = TTF_OpenFont("res/Pixel.ttf", 15);
	if (font == nullptr) {
		std::cout << "Font load failed" << std::endl;
		SDL_Quit();
		return SDL_FALSE;
	}
	return SDL_TRUE;
}

void SDLEngine::setWindowSize() {
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	UNG_Globals::SCREEN_W = DM.w / 2;
	UNG_Globals::SCREEN_H = DM.h / 2;
}
