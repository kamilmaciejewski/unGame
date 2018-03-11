/*
 * player.h
 *
 *  Created on: 9 mar 2018
 *      Author: Kamil
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include <SDL2/SDL.h>

#include <string>

class Player {
    int rotAngle;
    int posX;
    int posY;
    std::string skin;

public:
    Player();
    virtual ~Player();
    void draw(SDL_Surface *surface);
    void rotate(int angle);
    void move(float speed);
};

#endif /* PLAYER_H_ */
