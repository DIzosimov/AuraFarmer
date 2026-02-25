#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "raylib.h"

class Enemy {
  public:
    Enemy();

    void Spawn(Vector2 pos);
    void Update(Vector2 playerPos);
    void Draw();

    void TakeDamage(float amount);

    bool IsActive() const { return active; }
    void Deactivate() { active = false; }
    Vector2 GetPosition() const { return position; }
    float GetHealth() const { return health; }

  private:
    Vector2 position;
    bool active;
    float health;
    float maxHealth;
    float speed;
};

#endif