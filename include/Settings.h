/*
 * Settings.h
 *
 *  Created on: 16 lip 2018
 *      Author: Kamil
 */

#ifndef UNGAME_SETTINGS_H_
#define UNGAME_SETTINGS_H_

class Settings {
public:
  Settings();
  virtual ~Settings();

  bool draw_vectors = false;
  bool draw_textures = true;
  bool rotate = true;
  bool move = true;
  bool look = true;
};

#endif /* UNGAME_SETTINGS_H_ */
