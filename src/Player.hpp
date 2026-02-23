#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "raylib.h"

class Player {
  public:
    Player(Vector2 startPos);

    //Game Functions
    void Update();
    void Draw();

    //Getters
    Vector2 GetPosition() const { return position; }
    float GetAuraRadius() const { return auraRadius; }
    float GetAuraLevel() const { return auraLevel; }
    float GetCurrentExp() const { return experience; }
    float GetNextLevelExp() const { return nextLevelExperience; }

    //Setters
    void IncreaseAura(float amount); 

  private:
    Vector2 position;
    float speed;
    float auraRadius;
    float auraLevel;
    float experience;
    float nextLevelExperience;

    void CheckLevelUp();
};

#endif