/*
 * player.h
 *
 *  Created on: 9 mar 2018
 *      Author: Kamil
 */

#ifndef CREATURE_H_
#define CREATURE_H_

#include <SDL2/SDL.h>
#include "SDL2_rotozoom.h"

#include <string>

class Creature {
    float rot_angle, buffered_angle;
    std::string skin;
    SDL_Surface* surface = nullptr;
    SDL_Surface* optimized_surface = nullptr;
    SDL_Surface* rotated_Surface = nullptr;
    SDL_Rect rect_pos { 0, 0, 0, 0 };
    float pos_x, pos_y;
    float speed, rotation_speed;
    int rotation_step = 2;
    bool isCreatureOnScreen();

public:
    Creature();
    virtual ~Creature();
    void draw(SDL_Surface *);
    void update(uint32_t &);
    void move(long);
    void setPos(int, int);
    void rotate(float);
    void setRotationSpeed(float);
    void setSpeed(float);
};

#endif /* CREATURE_H_ */
