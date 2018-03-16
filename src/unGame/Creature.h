/*
 * player.h
 *
 *  Created on: 9 mar 2018
 *      Author: Kamil
 */

#ifndef CREATURE_H_
#define CREATURE_H_

#include <SDL2/SDL.h>

#include <string>

class Creature {
    int rotAngle;
    std::string skin;
    SDL_Surface* surface = NULL;
    SDL_Surface* optimizedSurface = NULL;
    SDL_Rect rectPos { 0, 0, 0, 0 };

public:
    int posX;
    int posY;
    Creature();
    virtual ~Creature();
    void draw(SDL_Surface *surface);
    void rotate(int angle);
    void move(int speed);
    void updatePos();
};

#endif /* CREATURE_H_ */
