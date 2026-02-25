#include <raylib.h>
#include "GameManager.hpp"

int main() {
    InitWindow(1280, 720, "Aura Farmer - Clean Architecture");
    SetTargetFPS(60);

    GameManager game; // Everything is tucked neatly inside here

    while (!WindowShouldClose()) {
        // UPDATE
        game.Update();

        // DRAW
        BeginDrawing();
            ClearBackground(BLACK);
            game.Draw();
            DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}