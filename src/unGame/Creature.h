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
    float rotAngle;
    std::string skin;
    SDL_Surface* surface = NULL;
    SDL_Surface* optimizedSurface = NULL;
    SDL_Surface* rotSurface = NULL;
    SDL_Rect rectPos { 0, 0, 0, 0 };
    float posX, posY;
    float speed, rotationSpeed;

public:
    Creature();
    virtual ~Creature();
    void draw(SDL_Surface *surface);
    void rotate(float angle);
    void move(float speed);
    void setPos(int posX, int posY);
    void setRotationAngle(float rotationAngle);
    void setRotationSpeed(float rotationSpeed);
    void setSpeed(float speed);
};

#endif /* CREATURE_H_ */
