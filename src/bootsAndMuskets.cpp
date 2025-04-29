#include <raylib.h>
#include "raymath.h"
#include <rcamera.h>
#include <iostream>
#include "globals.hpp"
#include "settings.hpp"
#include "math.hpp"
#include "map.hpp"

int main() {
    
    InitSettings();

    InitWindow(SETTINGS.game.WIDTH, SETTINGS.game.HEIGHT, "Boots and Muskets --- 0.0.1");
    InitAudioDevice();

    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    Region TestMap(64);
    Texture2D Water = LoadTexture("textures/water.png");

    SetTargetFPS(SETTINGS.game.TARGET_FPS);
    ToggleFullscreen();
    SetExitKey(SETTINGS.keybinds.GAME_CLOSE);

    while (!WindowShouldClose()){

        culled = 0;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f/camera.zoom);
            camera.target = Vector2Add(camera.target, delta);
        }
        float wheel = GetMouseWheelMove();
        if (wheel != 0){
            // Get the world point that is under the mouse
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);

            // Set the offset to where the mouse is
            camera.offset = GetMousePosition();

            // Set the target to match, so that the camera maps the world space point 
            // under the cursor to the screen space point under the cursor at any zoom
            camera.target = mouseWorldPos;

            // Zoom increment
            float scaleFactor = 1.0f + (0.25f*fabsf(wheel));
            if (wheel < 0) scaleFactor = 1.0f/scaleFactor;
                camera.zoom = Clamp(camera.zoom*scaleFactor, 0.125f, 4.0f);
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(SKYBLUE);
            BeginMode2D(camera);
                TestMap.DrawRegion(Water, camera);
            EndMode2D();
            DrawText(std::to_string(culled).insert(0, "Culled Chunks: ").c_str(), 0, 20, 20, WHITE);
            if (SETTINGS.game.SHOW_FPS)
                DrawFPS(0, 0);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
