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

    float gemSpawnTimer;
    float gemSpawnRate = 3.0f;  // Spawn a natural gem every 3 seconds
    
    float enemyWaveTimer;
    float enemyWaveRate = 10.0f; // Spawn a wave every 10 seconds

    void HandleCombat();
    void HandleHarvesting();
    void SpawnWave(int count);
    void CreateGemAt(Vector2 position);
    void SpawnInitialGems(int count);
};

#endif