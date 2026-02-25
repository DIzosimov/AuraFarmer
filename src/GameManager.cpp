#include "GameManager.hpp"
#include "raymath.h"

GameManager::GameManager() : player({640, 360}) {
  for(int i=0; i < MAX_ENEMIES; i++) enemyPool[i] = Enemy();
  for(int i=0; i < MAX_GEMS; i++) gemPool[i] = Gem();
  SpawnInitialGems(20); 
  enemyPool[0].Spawn({ 300, 300 });
  SpawnWave(10);
  gemSpawnTimer = 0.0f;
  enemyWaveTimer = 0.0f;
}

void GameManager::Update() {
float dt = GetFrameTime();
  player.Update();

  // --- 1. PERIODIC GEM SPAWNING ---
  gemSpawnTimer += dt;
  if (gemSpawnTimer >= gemSpawnRate) {
      // Spawn 1 basic gem somewhere random inside the screen
      Vector2 randomPos = { (float)GetRandomValue(100, 1180), (float)GetRandomValue(100, 620) };
      CreateGemAt(randomPos); 
      gemSpawnTimer = 0.0f;
  }

  // --- 2. PERIODIC ENEMY WAVES ---
  enemyWaveTimer += dt;
  if (enemyWaveTimer >= enemyWaveRate) {
      SpawnWave(5); // Spawn 5 enemies from the edges
      enemyWaveTimer = 0.0f;
      // Optional: Make it harder!
      // enemyWaveRate *= 0.95f; 
  }
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
        CreateGemAt(enemyPool[i].GetPosition());
      }
    }
  }
}

void GameManager::HandleHarvesting() {
  for (int i = 0; i < MAX_GEMS; i++) {
    if (!gemPool[i].IsActive()) continue;

    gemPool[i].Update();

    if (Vector2Distance(player.GetPosition(), 
        gemPool[i].GetPosition()) < player.GetAuraRadius()) 
    {
      player.IncreaseAura(gemPool[i].GetValue());
      gemPool[i].Deactivate();
      //RESPAWN GEM
    }
  }
}

void GameManager::Draw() {
  for (int i = 0; i < MAX_GEMS; i++) gemPool[i].Draw();
  for (int i = 0; i < MAX_ENEMIES; i++) enemyPool[i].Draw();
  player.Draw();
}

void GameManager::SpawnWave(int count) {
    int enemiesSpawnedThisWave = 0;

    for (int i = 0; i < MAX_ENEMIES; i++) {
        // 1. Only use this slot if it's currently inactive
        if (!enemyPool[i].IsActive()) {
            
            Vector2 spawnPos;
            int side = GetRandomValue(0, 3); 
            float offset = 80.0f; // Distance outside the screen

            // 2. Math for Screen Edges
            if (side == 0) { // Top
                spawnPos.x = (float)GetRandomValue(-offset, 1280 + offset);
                spawnPos.y = -offset;
            } else if (side == 1) { // Bottom
                spawnPos.x = (float)GetRandomValue(-offset, 1280 + offset);
                spawnPos.y = 720 + offset;
            } else if (side == 2) { // Left
                spawnPos.x = -offset;
                spawnPos.y = (float)GetRandomValue(-offset, 720 + offset);
            } else { // Right
                spawnPos.x = 1280 + offset;
                spawnPos.y = (float)GetRandomValue(-offset, 720 + offset);
            }

            // 3. ACTIVATE
            enemyPool[i].Spawn(spawnPos);
            enemiesSpawnedThisWave++;

            // 4. Stop once we've spawned the requested amount
            if (enemiesSpawnedThisWave >= count) break;
        }
    }
    
    // Debug Trace: Check your terminal/console to see if this prints!
    TraceLog(LOG_INFO, "Wave Spawned: %d enemies", enemiesSpawnedThisWave);
}

void GameManager::SpawnInitialGems(int count) {
    for (int i = 0; i < MAX_GEMS && count > 0; i++) {
        if (!gemPool[i].IsActive()) {
            Vector2 randomPos = { (float)GetRandomValue(100, 1100), (float)GetRandomValue(100, 600) };
            gemPool[i].Spawn(randomPos, BASIC);
            count--;
        }
    }
}

void GameManager::CreateGemAt(Vector2 pos) {
  for (int i = 0; i < MAX_GEMS; i++) {
    if (!gemPool[i].IsActive()) {
      int roll = GetRandomValue(1, 100);
      GemType type = BASIC;
      if (roll > 95) type = EPIC;
      else if (roll > 80) type = RARE;

      gemPool[i].Spawn(pos, type);
      break;
    }
  }
}