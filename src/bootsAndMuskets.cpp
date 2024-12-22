#include <raylib.h>
#include <iostream>
#include "globals.hpp"
#include "settings.hpp"
#include "scene.hpp"
#include "sprite.hpp"

int main() {

    InitWindow(WIDTH, HEIGHT, "Boots and Muskets --- 0.0.0");
    InitAudioDevice();
    
    ToggleFullscreen();
    InitSettings();

    LoadTextures();

    SetTargetFPS(SETTINGS.game.TARGET_FPS);
    SetExitKey(SETTINGS.keybinds.GAME_CLOSE);

    while (!WindowShouldClose()) {


        DeltaT = GetFrameTime();

        BeginDrawing();
            ClearBackground(BLACK);
            DrawFPS(0,0);
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}