#include <stdio.h>
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>

#include "Creature.h"

Creature::Creature(SDL_Surface* surfaceptr) {
  surface = surfaceptr;
}

Creature::~Creature() {
}

void Creature::draw(SDL_Renderer* renderer, const int* screenWidht,
    const int* screenHeight, Settings* settings) {
//TODO: Reuse preloaded texture.
    const int* screenHeight) {
  if (texture == nullptr) {
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_QueryTexture(texture, nullptr, nullptr, &rect_pos.w, &rect_pos.h);
  }

  if (isObjectOnScreen(screenWidht, screenHeight)) {
    if (settings->draw_textures) {
      SDL_RenderCopyEx(renderer, texture, nullptr, &rect_pos, -rot_angle,
          nullptr, SDL_FLIP_NONE);
      if (isActive) {
        SDL_RenderDrawRect(renderer, &rect_pos);
      }
    }
    if (settings->draw_vectors) {
      vector.draw(renderer);

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
