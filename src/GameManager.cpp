#include "GameManager.hpp"
#include "raymath.h"

GameManager::GameManager() : player({640, 360}) {
  //Initial Wavespawn  
  SpawnWave();
}

void GameManager::Update() {
  player.Update();
  HandleCombat();
  HandleHarvesting();
}

void GameManager::HandleCombat() {
  for (int i = 0; i < MAX_ENEMIES; i++) {
    if (!enemyPool[i].IsActive()) continue;

    enemyPool[i].Update(player.GetPosition());

    if (CheckCollisionCircles(
        player.GetPosition(), player.GetAuraRadius(), 
        enemyPool[i].GetPosition(), 10)) 
    {
      enemyPool[i].TakeDamage(15.0f * GetFrameTime());

      if (enemyPool[i].GetHealth() <= 0) {
        //SPAWN GEM
      }
    }
  }
}

void GameManager::HandleHarvesting() {
  for (int i = 0; i < MAX_GEMS; i++) {
    if (!gemPool[i].IsActive()) continue;

    gemPool[i].Update();

    if (Vector2Distance(player.GetPosition(), gemPool[i].GetPosition()) < player.GetAuraRadius()) {
            player.IncreaseAura(gemPool[i].GetValue());
            gemPool[i].Deactivate();
            //RESPAWN GEM
        }
  }
}