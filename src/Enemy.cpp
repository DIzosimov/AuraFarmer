#include "Enemy.hpp"
#include "raymath.h"

Enemy::Enemy() {
  active = false;
  health = 0;
  position = { 0, 0 };
}

void Enemy::Spawn(Vector2 pos) {
  position = pos;
  maxHealth = 20.0f;
  health = maxHealth;
  speed = 80.0f;
  active = true;
}

void Enemy::Update(Vector2 playerPos) {
  if (!active) return;

  //Direction towards player
  Vector2 direction = Vector2Subtract(playerPos, position);

  //Normalize movement
  direction = Vector2Normalize(direction);

  //Move
  position.x += direction.x * speed * GetFrameTime();
  position.y += direction.y * speed * GetFrameTime();

  //Death Check
  if (health <= 0) {
    active = false;
  }
}

void Enemy::TakeDamage(float amount) {
  health -= amount;
}

void Enemy::Draw() {
  if (!active) return;

  DrawCircleV(position, 10, RED);

  float healthBarWidth = 20.0f * (health / maxHealth);
  DrawRectangle(position.x - 10, position.y - 15, 20, 3, DARKGRAY);
  DrawRectangle(position.x - 10, position.y -15, healthBarWidth, 3, MAROON);
}