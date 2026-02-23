#include <raylib.h>
#include <raymath.h>
#include <vector>   
#include "Player.hpp"
#include "Gem.hpp"

int main()
{
    // Initialize window
    const int screenWidth = 1280;
    const int screenHeight = 720;
    
    InitWindow(screenWidth, screenHeight, "Aura Farmer");
    SetTargetFPS(60);
    
    //Player Setup
    Vector2 playerPosition = { screenWidth/2.0f, screenHeight/2.0f };
    float playerSize = 50.0f;
    float playerSpeed = 200.0f;
    Player player({ playerPosition });

    //Gem Setup
    const int MAX_GEMS = 50;
    Gem gemPool[MAX_GEMS];

    for (int i = 0; i < 20; i++) {
        Vector2 randomPos = { (float)GetRandomValue(100, 1100), (float)GetRandomValue(100, 600) };
        gemPool[i].Spawn(randomPos, BASIC);
    }


    // Game loop
    while (!WindowShouldClose())
    {
        // Update
        player.Update();

        //Gems
        for (int i = 0; i < MAX_GEMS; i++) {
            if (gemPool[i].isActive()) {
                gemPool[i].Update();
            }
            //COLLISION DETECTION
            float dist = Vector2Distance(player.GetPosition(), gemPool[i].GetPosition());

            //If distance < aura radius, harvest (change to magnet?)
            if (dist < player.GetAuraRadius()) {
                player.IncreaseAura(gemPool[i].GetValue());
                gemPool[i].Deactivate();

                //RESPAWN
                Vector2 newPos = {
                    (float)GetRandomValue(50, screenWidth - 50), 
                    (float)GetRandomValue(50, screenHeight - 50)
                };
                gemPool[i].Spawn(newPos, BASIC);
            }
        }
        // Draw
        BeginDrawing();
        
            ClearBackground(BLACK);

            for (int i = 0; i < MAX_GEMS; i++) {
                gemPool[i].Draw();
            }

            player.Draw();

            DrawText("Aura Level: Growing", 10, 10, 20, RAYWHITE);
            
        EndDrawing();
    }
    
    // Cleanup
    CloseWindow();
    
    return 0;
}