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

static const SDL_Rect neuralBox = { 1000, 5, 525, 775 };
static const SDL_Rect worldBox = {5, 5, 990, 775 };
}
#endif /* UNGAME_GLOBALS_H_ */
