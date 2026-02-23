#include "Player.hpp"
#include "raymath.h"

Player::Player(Vector2 startPos) {
  position = startPos;
  speed = 250.0f;
  auraRadius = 50.0f;
  auraLevel = 10.0f;
}

void Player::Update() {
  float dt = GetFrameTime();

  if (IsKeyDown(KEY_W)) position.y -= speed * dt;
  if (IsKeyDown(KEY_S)) position.y += speed * dt;
  if (IsKeyDown(KEY_A)) position.x -= speed * dt;
  if (IsKeyDown(KEY_D)) position.x += speed * dt;
}

void Player::Draw() {
  //Player
  DrawCircleV(position, 15, BLUE);

  //Aura
  DrawCircleV(position, auraRadius, ColorAlpha(GOLD, 0.3f));

  //Outline
  DrawCircleLines(position.x, position.y, auraRadius, GOLD);
}

//EXP GAIN + LEVEL UP LOGIC
void Player::IncreaseAura(float amount) {
  auraRadius += amount;

  if (GetCurrentExp() >= GetNextLevelExp()) {
    auraLevel++;
    experience = 0;
    nextLevelExperience *= 1.2f;
    auraRadius += 10.0f;

    //ADD VISUALS HERE
  }
}