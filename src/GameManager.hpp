#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "Player.hpp"
#include "Enemy.hpp"
#include "Gem.hpp"
#include <vector>

class GameManager {
  public:
    GameManager();

    void Update();
    void Draw();

  private:
    static const int MAX_ENEMIES = 100;
    static const int MAX_GEMS = 50;
  
    Player player;
    Enemy enemyPool[MAX_ENEMIES];
    Gem gemPool[MAX_GEMS];

    void HandleCombat();
    void HandleHarvesting();
    void SpawnWave();
};

#endif