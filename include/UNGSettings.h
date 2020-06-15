#ifndef UNGAME_SETTINGS_H_
#define UNGAME_SETTINGS_H_

#include <string>
#include <SDL2/SDL.h>
class Settings {
public:
enum MODE{CONSOLE, GUI};
  Settings();
  virtual ~Settings();

  MODE mode = MODE::GUI;
  SDL_Point mousePos;
  bool isRunning = true;
  bool btn_down = false;
  bool btn_down_left = false;
  bool btn_down_right = false;
  bool draw_vectors = false;
  bool mark_active = false;
  bool draw_textures = true;
  bool rotate = true;
  bool move = true;
  bool look = true;
  bool creature = true;
  float timeScale = 1;
};

#endif /* UNGAME_SETTINGS_H_ */
