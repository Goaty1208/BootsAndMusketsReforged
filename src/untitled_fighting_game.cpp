#include <raylib.h>
#include <iostream>
#include "globals.hpp"
#include "player.hpp"

int main() {

    Player left;

    InitWindow(WIDTH, HEIGHT, "Untitled Fighting Game --- 0.0.0");

    SetTargetFPS(FPS);

    while (!WindowShouldClose()) {

        DeltaT = GetFrameTime();

        left.Tick();

        BeginDrawing();
            ClearBackground(BLUE);
            DrawFPS(0,0);
            left.Draw();
        EndDrawing();
    }
    

    return 0;
}