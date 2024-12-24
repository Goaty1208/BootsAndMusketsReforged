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

    InitWindow(SETTINGS.game.WIDTH, SETTINGS.game.HEIGHT, "Boots and Muskets --- 0.0.0");
    InitAudioDevice();

    LoadTextures();

    SetTargetFPS(SETTINGS.game.TARGET_FPS);
    SetExitKey(SETTINGS.keybinds.GAME_CLOSE);

    Scene scene(GAME);
    Sprite test(0, 0.0f, 0.0f);

    while (!WindowShouldClose()) {

        DeltaT = GetFrameTime();

        scene.Update();

        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(scene.GetCamera());
                scene.DrawSceneSprites();
            EndMode2D();
            scene.DrawSceneGUI();
            //Indipendent of the scene, you 
            //should ALWAYS render FPS on top for debugging reasons
            if(SETTINGS.game.SHOW_FPS)
                DrawFPS(0,0);
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}