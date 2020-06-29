#ifndef UNGAME_GLOBALS_H_
#define UNGAME_GLOBALS_H_

namespace UNG_Globals {
inline int SCREEN_H = 100;
inline int SCREEN_W = 100;
enum engine {
	SDLEngine, UNGEngine, WORLDEngine
};
					        		   //0xAA BB GG RR
static const uint32_t RED =   			 0xFF'00'00'FF;
static const uint32_t GREEN = 			 0xFF'00'FF'00;
static const uint32_t GREY_TRANSPARENT = 0x88'FF'FF'FF;

static const char neuralBoxTitle[] = "";
static const SDL_Rect neuralBox = { 1000, 5, 525, 775 };
static const int offset = 5;

static const char neuralBoxInputTitle[] = "input";
static const SDL_Rect neuralBoxInput = { neuralBox.x+offset, neuralBox.y+offset, 200, neuralBox.h-(2*offset) };

static const int hiddenLayrerOverlap = 150;
static const char neuralBoxHiddenTitle[] = "hidden";
static const SDL_Rect neuralBoxHidden = { neuralBoxInput.x + neuralBoxInput.w - hiddenLayrerOverlap,
		neuralBox.y+ (2*offset), 450, neuralBox.h-(4*offset) };

static const int outputLayrerOverlap = 100;
static const char neuralBoxOutputTitle[] = "output";
static const SDL_Rect neuralBoxOutput = { neuralBoxHidden.x + neuralBoxHidden.w - outputLayrerOverlap,
		neuralBox.y+offset, 500, neuralBox.h-(2*offset) };


static const SDL_Rect worldBox = {5, 5, 990, 775 };
}
#endif /* UNGAME_GLOBALS_H_ */
