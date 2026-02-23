#include "Gem.hpp"
#include <math.h>

Gem::Gem() {
  active = false;
  position = { 0, 0 };
  expValue = 0;
  pulse = 0;
}

void Gem::Spawn(Vector2 pos, GemType type) {
  this->position = pos;
  this->type = type;
  this->active = true;

  switch (type)
  {
  case BASIC: 
    expValue = 5;
    break;
  case RARE:
    expValue = 25;
    break;
  case EPIC:
    expValue = 100;
    break;
  default:
    break;
  }
}

void Gem::Update() {
  if (!isActive) return;

  pulse += GetFrameTime() * 5.0f;
}

void Gem::Draw() {
  if (!isActive) return;

  Color gemColor = GREEN;
  if (type == RARE) gemColor = BLUE;
  if (type == EPIC) gemColor = PURPLE;
  DrawCircleV(position, 6.0f, gemColor);
} 

