#ifndef UNGAME_SETTINGS_H_
#define UNGAME_SETTINGS_H_

class Settings {
public:

  Settings();
  virtual ~Settings();

  bool btn_down = false;
  bool draw_vectors = false;
  bool mark_active = false;
  bool draw_textures = true;
  bool rotate = true;
  bool move = true;
  bool look = true;
};

#endif /* UNGAME_SETTINGS_H_ */
