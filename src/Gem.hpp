#ifndef GEM_HPP
#define GEM_HPP

#include "raylib.h"

enum GemType { BASIC, RARE, EPIC };

class Gem {
  public:
    Gem();

    //Logic
    void Spawn(Vector2 pos, GemType type);
    void Update();
    void Draw();

    //Data
    bool IsActive() const { return active; }
    Vector2 GetPosition() const { return position; }
    float GetValue() const { return expValue; }

    //Switch
    void Deactivate() { active = false; }

  private:
    GemType type;
    Vector2 position;
    bool active;
    float expValue;
    float pulse;
};

#endif