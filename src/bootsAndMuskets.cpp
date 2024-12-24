#include <raylib.h>
#include <iostream>
#include "globals.hpp"
#include "settings.hpp"
#include "scene.hpp"
#include "sprite.hpp"

int main() {

    InitWindow(WIDTH, HEIGHT, "Boots and Muskets --- 0.0.0");
    InitAudioDevice();
    
    //ToggleFullscreen();
    //WIDTH = GetScreenWidth();
    //HEIGHT = GetScreenHeight();
    InitSettings();

    LoadTextures();

    SetTargetFPS(SETTINGS.game.TARGET_FPS);
    SetExitKey(SETTINGS.keybinds.GAME_CLOSE);

    Scene scene(GAME);
    Sprite test(0, 0.0f, 0.0f);
    scene.AddSprite(test);

    while (!WindowShouldClose()) {

        DeltaT = GetFrameTime();

        scene.Update();

        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(scene.GetCamera());
                scene.DrawSceneSprites();
            EndMode2D();
            scene.DrawSceneGUI();
            DrawFPS(0,0);
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}