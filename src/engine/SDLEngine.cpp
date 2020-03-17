#include <iostream>

#include "SDLEngine.h"

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

void SDLEngine::run(World *world) {
	threadSDL = std::thread(&SDLEngine::runThread, this, world);
}
void SDLEngine::runThread(World *world) {
	log("SDL engine world running");
	while (isRunning) {
		SdlEventHandler.handleEvents(&isRunning, settings);
		clearScreen();
		world->markActiveObjectByMousePos(SdlEventHandler.mousePos);
		world->draw(renderer);
		updateFPSInfo();
		drawActiveCreatureInfo(world->infoStr);
		draw();
		countFPS(&fps_res, &msStart, &msEnd, &fps_counter);
	}
	log("SDL engine world running stop");
	close();
}
void SDLEngine::clearScreen() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}
void SDLEngine::draw() {
	SDL_RenderCopy(renderer, fps_texture, nullptr, &fps_dstrect);
	SDL_RenderCopy(renderer, info_texture, nullptr, &info_dstrect);
	SDL_DestroyTexture(fps_texture);
	SDL_DestroyTexture(info_texture);
	SDL_RenderPresent(renderer);
}

void SDLEngine::stop() {
	isRunning = false;
	threadSDL.join();
	close();
}
void SDLEngine::log(std::string message) {
	if (logger != nullptr) {
		logger->push(message);
	}
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
		SDL_Quit();
	}
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
		log("TTF_Init failed");
		SDL_Quit();
		return SDL_FALSE;
	}
	font = TTF_OpenFont("res/Pixel.ttf", 15);
	if (font == nullptr) {
		log("Font load failed");
		SDL_Quit();
		return SDL_FALSE;
	}
	return SDL_TRUE;
}

void SDLEngine::setWindowSize() {
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	UNG_Globals::SCREEN_W = DM.w * 0.8;
	UNG_Globals::SCREEN_H = DM.h * 0.8;
}
