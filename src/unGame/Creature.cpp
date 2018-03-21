#include <stdio.h>
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

#include "Creature.h"

Creature::Creature() {
  surface = SDL_LoadBMP("res/arrow.bmp");
  SDL_SetColorKey(surface, SDL_TRUE,
      SDL_MapRGB(surface->format, 0xff, 0x0, 0xff));
  optimized_surface = SDL_ConvertSurface(surface, surface->format, 0);
  rotated_Surface = rotozoomSurface(optimized_surface, rot_angle, 1, 0);
  SDL_FreeSurface(surface);

  if (surface == nullptr) {
    printf("Unable to load image: %s\n", SDL_GetError());
  }
}

Creature::~Creature() {
  if (optimized_surface != nullptr) {
    SDL_FreeSurface(optimized_surface);
  }
  if (rotated_Surface != nullptr) {
    SDL_FreeSurface(rotated_Surface);
  }
}

void Creature::draw(SDL_Surface* destSurface) {
  if (isCreatureOnScreen()) {
    SDL_BlitSurface(rotated_Surface, nullptr, destSurface, &rect_pos);
  }
}

bool Creature::isCreatureOnScreen() {
  return (rect_pos.x >= (-rect_pos.w) && rect_pos.y >= (-rect_pos.h)
      && rect_pos.x <= (SCREEN_WIDTH + rect_pos.w)
      && rect_pos.y <= (SCREEN_HEIGHT + rect_pos.h));
}

void Creature::update(uint32_t & timeDelta) {
  rotate(rotation_speed * timeDelta);
  move(timeDelta);
}

void Creature::setPos(int newPosX, int newPosY) {
  pos_x = newPosX;
  pos_y = newPosY;
  rect_pos.x = pos_x;
  rect_pos.y = pos_y;
}

void Creature::rotate(float rotationAngle) {
  buffered_angle += rotationAngle;
  rot_angle += rotationAngle;
  if (rot_angle > 360) {
    rot_angle -= 360;
  }
  if (rot_angle < -360) {
    rot_angle += 360;
  }

  if (isCreatureOnScreen()
      && (buffered_angle >= rotation_step || buffered_angle <= -rotation_step)) {
    SDL_FreeSurface(rotated_Surface);
    rotated_Surface = rotozoomSurface(optimized_surface, rot_angle, 1, 0);
    buffered_angle = 0;
  }
  rect_pos.x = pos_x - rotated_Surface->w / 2 - optimized_surface->w / 2;
  rect_pos.y = pos_y - rotated_Surface->h / 2 - optimized_surface->h / 2;
}

void Creature::move(long time_delta) {
  pos_x += sin(rot_angle * M_PI / 180) * speed * time_delta;
  pos_y += cos(rot_angle * M_PI / 180) * speed * time_delta;
}

void Creature::setSpeed(float speed) {
  this->speed = speed;
}
void Creature::setRotationSpeed(float speed) {
  this->rotation_speed = speed;
}
