#include <iostream>
#include <string>
#include "SDLEngine.h"

SDLEngine::~SDLEngine() {
	delete logger;
	logger = nullptr;
}

SDL_bool SDLEngine::init(Settings *settings_) {
	settings = settings_;

	logger = LoggingHandler::getLogger("SDL");
	timeFrameHandler.setLogger(logger);

	if (!initSDLEngine()) {
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

void SDLEngine::run(World *world, Settings *settings) {
	if (settings->mode != Settings::MODE::GUI) {
		return;
	}
	this->settings = settings;
	threadSDL = std::thread(&SDLEngine::runThread, this, world);
}
void SDLEngine::runThread(World *world) {

	init(settings);
	logger->log("world running");
	while (isRunning) {
		SdlEventHandler.handleEvents(&isRunning, settings);
		clearScreen();
		world->handleInput();
		world->draw(renderer);
//		drawActiveCreatureInfo(world->infoStr);
		draw();
		timeFrameHandler.frameTick();
	}
	logger->log("world stopped");
	logger->reportFps(0);
	close();
}
void SDLEngine::clearScreen() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}
void SDLEngine::draw() {
	SDL_SetRenderDrawColor(renderer, 88, 88, 88, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawRect(renderer, &(UNG_Globals::worldBox));
//	SDL_RenderCopy(renderer, info_texture, nullptr, &info_dstrect);
//	SDL_DestroyTexture(info_texture);
	SDL_RenderPresent(renderer);
}

void SDLEngine::stop() {
	isRunning = false;
	if (threadSDL.joinable()) {
		threadSDL.join();
	}
	close();
}

void SDLEngine::close() {
	if (window != nullptr) {
		SDL_DestroyWindow(window);
	};
	if (renderer != nullptr) {
		SDL_DestroyRenderer(renderer);
	}
	window = nullptr;
	renderer = nullptr;
	if (font != nullptr) {
		TTF_CloseFont(font);
	}
	font = nullptr;
	if (TTF_WasInit()) {
		TTF_Quit();
	}
	if (SDL_WasInit(SDL_INIT_VIDEO)) {
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
	}
	if (logger != nullptr) {
		delete logger;
		logger = nullptr;
	}
}

void SDLEngine::drawActiveCreatureInfo(std::string infoStr) {
	info_surface = TTF_RenderText_Solid(font, infoStr.c_str(), color);
	info_texture = SDL_CreateTextureFromSurface(renderer, info_surface);
	SDL_QueryTexture(info_texture, nullptr, nullptr, &info_dstrect.w,
			&info_dstrect.h);
	SDL_FreeSurface(info_surface);
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
		logger->log("init: TTF_Init failed");
		SDL_Quit();
		return SDL_FALSE;
	}
	font = TTF_OpenFont("res/Pixel.ttf", 15);
	if (font == nullptr) {
		logger->log("init: font load failed");
		SDL_Quit();
		return SDL_FALSE;
	}
	return SDL_TRUE;
}
SDL_bool SDLEngine::initSDLEngine() {
	if (!SDL_WasInit(SDL_INIT_VIDEO)) {
		if (SDL_Init( SDL_INIT_VIDEO) < 0) {
			SDL_Log("init: Unable to initialize SDL: %s", SDL_GetError());
			logger->log("init: Unable to initialize SDL:");
			logger->log(SDL_GetError());
		} else {
			return SDL_TRUE;
		}
	} else {
		return SDL_TRUE;
	}
	return SDL_FALSE;
}

void SDLEngine::setWindowSize() {
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	UNG_Globals::SCREEN_W = DM.w * 0.8;
	UNG_Globals::SCREEN_H = DM.h * 0.8;
}
