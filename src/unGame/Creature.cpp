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
//  vector = new Vector();

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

void Creature::draw(SDL_Renderer* renderer, const int* screenWidht,
    const int* screenHeight) {
//TODO: Reuse preloaded texture.
  if (texture == nullptr) {
    texture = SDL_CreateTextureFromSurface(renderer, optimized_surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &rect_pos.w, &rect_pos.h);
  }
  if (isObjectOnScreen(screenWidht, screenHeight)) {
    SDL_RenderCopyEx(renderer, texture, nullptr, &rect_pos, -rot_angle, nullptr,
        SDL_FLIP_NONE);
//    vector.draw(renderer);
    if (isActive) {
    SDL_RenderDrawRect(renderer, &rect_pos);
    }
  }
}

void Creature::update(const uint32_t* timeDelta) {
  rotate(rotation_speed * *timeDelta);
  move(timeDelta);
}

void Creature::rotate(float rotationAngle) {
  rot_angle += rotationAngle;
  if (rot_angle > 360) {
    rot_angle -= 360;
  }
  if (rot_angle < -360) {
    rot_angle += 360;
  }

  rect_pos.x = pos_x; // - rotated_Surface->w / 2 - optimized_surface->w / 2;
  rect_pos.y = pos_y; // - rotated_Surface->h / 2 - optimized_surface->h / 2;
}

void Creature::move(const uint32_t* time_delta) {
  pos_x += sin(rot_angle * M_PI / 180) * speed * *time_delta;
  pos_y += cos(rot_angle * M_PI / 180) * speed * *time_delta;
  vector.setPos(&pos_x, &pos_y);
}

void Creature::setSpeed(float speed) {
  this->speed = speed;
}
void Creature::setRotationSpeed(float speed) {
  this->rotation_speed = speed;
}
