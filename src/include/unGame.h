/*
 * unGame.h
 *
 *  Created on: 10 mar 2018
 *      Author: Kamil
 */

#ifndef UNGAME_H_
#define UNGAME_H_

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

bool init();
bool loadMedia();
void close();

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* imageSurface = NULL;


#endif /* UNGAME_H_ */
