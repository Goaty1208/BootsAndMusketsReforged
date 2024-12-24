#include <raylib.h>
#include <iostream>
#include "globals.hpp"
#include "settings.hpp"
#include "scene.hpp"
#include "sprite.hpp"

int main() {
    
    //ToggleFullscreen();
    //SETTINGS.game.WIDTH = GetScreenWidth();
    //SETTINGS.game.HEIGHT = GetScreenHeight();
    
    InitSettings();

    InitWindow(SETTINGS.game.WIDTH, SETTINGS.game.HEIGHT, "Boots and Muskets --- 0.0.1");
    InitAudioDevice();

    LoadTextures();

    SetTargetFPS(SETTINGS.game.TARGET_FPS);
    SetExitKey(SETTINGS.keybinds.GAME_CLOSE);

    Scene scene(GAME);
    #ifdef DEBUG
        Sprite test(0, 0.0f, 0.0f);
        scene.AddSprite(test);
    #endif

    while (!WindowShouldClose()) {

        DeltaT = GetFrameTime();

        scene.Update();

        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(scene.GetCamera());
                scene.DrawSceneSprites();
            EndMode2D();
            scene.DrawSceneGUI();
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}