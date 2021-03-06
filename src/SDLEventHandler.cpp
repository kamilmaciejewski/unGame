#include "SDLEventHandler.h"

void SDLEventHandler::handleEvents(bool* result, Settings* settings) {
  while (SDL_PollEvent(&ev) != 0) {
    switch (ev.type) {
    case SDL_QUIT: {
      *result = false;
      break;
    }
	case SDL_MOUSEBUTTONDOWN: {
		if (ev.button.button == SDL_BUTTON_LEFT) {
			if (!settings->btn_down_left) {
				settings->btn_down_left = true;
				settings->mark_active = true;
			}
			break;
		} else if (ev.button.button == SDL_BUTTON_RIGHT) {
			if (!settings->btn_down_right) {
				settings->btn_down_right = true;
				settings->mark_active = true;
			}
			break;
		}
		break;
	}
	case SDL_MOUSEBUTTONUP: {
		if (ev.button.button == SDL_BUTTON_LEFT) {
			settings->btn_down_left = false;
			settings->mark_active = false;
			break;
		} else if (ev.button.button == SDL_BUTTON_RIGHT) {
			settings->btn_down_right = false;
			break;
		}
		break;
	}
    case SDL_KEYDOWN: {
      switch (ev.key.keysym.scancode) {
      case SDL_SCANCODE_V:
        settings->draw_vectors = !settings->draw_vectors;
        break;
      case SDL_SCANCODE_T:
        settings->draw_textures = !settings->draw_textures;
        break;
      case SDL_SCANCODE_R:
        settings->rotate = !settings->rotate;
        break;
      case SDL_SCANCODE_M:
        settings->move = !settings->move;
        break;
      case SDL_SCANCODE_L:
        settings->look = !settings->look;
        break;
      case SDL_SCANCODE_C:
	  settings->creature = !settings->creature;
	  	break;
      case SDL_SCANCODE_ESCAPE:
        *result = false;
        break;
      default:
        break;
      }
      break;
    }
    case SDL_MOUSEMOTION: {
      settings->mousePos.x = ev.motion.x;
      settings->mousePos.y = ev.motion.y;
      break;
    }
    default: {
      break;
    }
    }
  }
}
